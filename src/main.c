#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_INPUT 256
#define MAX_WORD_LENGTH 30

//Struct for the output 
typedef struct{
	char *word;
	uint8_t edit_distance;
} output_element;

//Array that saves the three words with the least edit distance
output_element output[5]={0};

uint8_t minThree(uint8_t a, uint8_t b, uint8_t c){
	uint8_t min = a;
	if(a>b) min = b;
	if(a>c) min = c;
	return min;
}

//Calculate the edit distance between two strings with the Wagner-Fischer-Algorithm
uint8_t distance(char *string_a, uint8_t string_a_length, char *string_b, uint8_t string_b_length){
	//Special cases if one string is empty
	if(string_a_length==0) return string_b_length;
	if(string_b_length==0) return string_a_length;

	//Create a Matrix for the calculation
	uint8_t matrix[string_a_length+1][string_b_length+1];
	
	//Set all Values to zero
	for(uint8_t a=0; a<=string_a_length; a++) for(uint8_t b=0; b<=string_b_length; b++) matrix[a][b] = 0;	
	
	//Fill the first row and column (identical for every string combination)
	for(uint8_t i=0; i<=string_a_length; i++) matrix[i][0]=i;
	for(uint8_t i=0; i<=string_b_length; i++) matrix[0][i]=i;
	
	for(uint8_t a=1; a<=string_a_length; a++){
		for(uint8_t b=1; b<=string_b_length; b++){
			//If one letter of both strings is equal the edit distance doesnt increment
			if(string_a[a-1]==string_b[b-1]) matrix[a][b]=matrix[a-1][b-1];
			else{
				matrix[a][b]=minThree(matrix[a-1][b-1], matrix[a-1][b], matrix[a][b-1])+1;
			}
		}
	}
	
	return matrix[string_a_length][string_b_length];
}

int main(int argc, const char *argv[]){
	printf("[Wagner-Fischer-Algorithm Demonstration]\n<Insert word:> ");
	//Variable for the User-Input
	char *user_input = (char *)malloc(MAX_INPUT);
	if(user_input==NULL){
		printf("%s: Memory full!\n", argv[0]);
		return 1;
	}
	//Read user_input with fgets from stdin
	fgets(user_input, MAX_INPUT, stdin);
	uint8_t input_length = strlen(user_input);
	//Delete the newline symbol from the user_input if there is one
	if(input_length>0 && (user_input[input_length-1]=='\n')){
		user_input[input_length-1] = '\0';
		input_length--;
	}

	//Open file with list of words
	FILE *wordlist = fopen("build/wordlist.txt", "r");
	if(wordlist==NULL){
		printf("%s: Failed to open file \"build/wordlist.txt\"!\n", argv[0]);
		return 1;
	}

	//Read the words from the list und calculate the edit distance
	char word[MAX_WORD_LENGTH]={0};
	uint8_t word_length;
	uint8_t edit_distance;
	while(fgets(word,MAX_WORD_LENGTH,wordlist)!=NULL){
		word_length = strlen(word);
		//Delete the newline symbol from the user_input if there is one
		if(word_length>0 && (word[word_length-1]=='\n')){
			word[word_length-1] = '\0';
			word_length--;
		}
		//Calculate and save the edit distance
		edit_distance = distance(user_input,input_length,word,word_length);
		//Iterate trough the output elements and check if the new word have a better edit distance
		for(uint8_t i=0; i<5; i++){
			//If an output element is null => insert the current word
			if(output[i].word==NULL){
				output[i].word = (char *)malloc(sizeof(char)*word_length);
				strcpy(output[i].word, word);
				output[i].edit_distance = edit_distance;
				break;
			}
			//If an output element has a bigger edit distance then the current word => insert the new one
			if(output[i].edit_distance > edit_distance){
				free(output[i].word);
				output[i].word = (char *)malloc(sizeof(char)*word_length);
				strcpy(output[i].word, word);
				output[i].edit_distance = edit_distance;
				break;
			}
		}

	}
	for(uint8_t i=0; i<5; i++) printf("%s = %d\n",output[i].word,output[i].edit_distance);
	fclose(wordlist);
	//Free the memory
	free(user_input);
	return 0;
}
