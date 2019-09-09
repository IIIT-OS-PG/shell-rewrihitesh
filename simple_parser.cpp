// written on 2 sep 2:30am 
// @uthor rewrihitesh
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "in.h"

char *command_parser(char *input)
{
	int tokenCount = 0;
	char *token;

	/* 
	allocate memory for the cmd structure 

	calloc creates memory and intilize it zero

	calloc creates ARG_MAX_COUNT -> number of blocks

	*/
	struct command *cmd = (command *)calloc(sizeof(struct command) +
				     ARG_MAX_COUNT * sizeof(char *), 1);

	if (cmd == NULL) {
		fprintf(stderr, "error: memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	/* 
	strtok splits the token of input[] 

	strtok(&array , char *delimiter);

	return null when string is endede

	get token by splitting on whitespace *

	*/
	token = strtok(input, " ");

	while (token != NULL && tokenCount < ARG_MAX_COUNT) {
		cmd->argv[tokenCount++] = token;
		token = strtok(NULL, " ");
	}
	cmd->name = cmd->argv[0];
	cmd->argc = tokenCount;
	return cmd;
}

int main(int argc, char const *argv[])
{
		
	char* g = _input();

	printf("%s\n",g);

	return 0;
}