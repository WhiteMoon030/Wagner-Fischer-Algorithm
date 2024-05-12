compiler=gcc
source_file=src/main.c
destination=build/wfa

compile: $(source_file) build/
	@$(compiler) $(source_file) -o $(destination)
	@echo "Compiled to $(destination)!"
clean: $(destination)
	@rm -f $(destination)
	@echo "Deleted $(destination)!"
run:
	@./$(destination)
