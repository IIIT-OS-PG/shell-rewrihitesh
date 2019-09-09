// written on 2 sep 8pm 
// @uthor rewrihitesh
// free the memory after consuming the input pointer

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pwd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<bits/stdc++.h>

#include "definitions.h"

bool isEmpty(char *input){
	if(input[0]=='\0')
		return true;
	return false;
}

bool is_file_exsists(std::string s){
	std::ifstream f(s);
    return f.good();
}

char *_input(void)
{
	long long buffer_size=2048;
	// maximum size of buffer
	char *get_the_char = (char *)malloc(buffer_size * sizeof(char));

	// if (get_the_char == NULL) {
	// 	fprintf(stderr, "error: malloc failed\n");
	// 	free(get_the_char);
	// 	exit(-1);
	// }

	int i = 0;
	char x;
	while ((x = getchar()) != '\n') {
		/* 
		did user enter ctrl+d ?
		ctrl+d will break the input and return EOF and we check for eof break out of loop
		*/
		if (x == EOF) {
			free(get_the_char);
			return NULL;
		}
		// allocate more memory for input 
		if (i >= buffer_size) {
			buffer_size = 2 * buffer_size;
			get_the_char = (char*)realloc(get_the_char, buffer_size);
		}

		get_the_char[i++] = x;
	}

	get_the_char[i] = '\0';
	return get_the_char;
}

std::string convertToString(char* a, int size) 
{ 
    int counter = 0; 
    std::string s = ""; 
    for (;counter < size; counter++) { 
        s = s + a[counter]; 
    } 
    return s; 
} 
