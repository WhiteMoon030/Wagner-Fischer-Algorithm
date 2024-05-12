#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_INPUT 256
#define MAX_WORD_LENGTH 30

//Calculate the edit distance of two strings with the Wagner-Fischer-Algorithm
uint8_t distance(char *string_a, uint8_t string_a_length, char *string_b, uint8_t string_b_length){
	return 0;
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
	while(fgets(word,MAX_WORD_LENGTH,wordlist)!=NULL){
		word_length = strlen(user_input);
		//Delete the newline symbol from the user_input if there is one
		if(word_length>0 && (word[word_length-1]=='\n')){
			word[word_length-1] = '\0';
			word_length--;
		}
		printf("%s, %d\n",word,word_length);
	}
	fclose(wordlist);
	//Free the memory
	free(user_input);
	return 0;
}
