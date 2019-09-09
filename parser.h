// written on 2 sep 2:30am 
// @uthor rewrihitesh

#include "in.h"
#include <deque>
using std::vector;	
char* read_file[500];
char* path;
char* home;
char* hostname;
char* user;
char* shell;
char* prompt;

command *command_parser(char *get_input)
{
	int tokenCount = 0;
	char *token;
	char *saveRecursivePtr;
	/* 
	allocate memory for the cmd structure 

	calloc creates memory and intilize it zero

	calloc creates ARG_MAX_COUNT -> number of blocks

	*/
	command *cmd = (command *)malloc(sizeof(command) +
				     ARG_MAX_COUNT * sizeof(char *));


	if (cmd == NULL) {
		fprintf(stderr, "error: memory allocation error\n");
		exit(-1);
	}

	/* 
	strtok splits the token of get_input

	strtok(&array , char *delimiter);

	return null when string is endede

	get token by splitting on whitespace *

	*/
	
	token = strtok_r(get_input, " ",&saveRecursivePtr);

	while (token != NULL && tokenCount < ARG_MAX_COUNT) {
		cmd->argv[tokenCount++] = token;
		token = strtok_r(NULL, " ",&saveRecursivePtr);
	}
	cmd->name = cmd->argv[0];
	if(cmd->argv[0][0] == '"' || cmd->argv[0][0] == '\'' ){
		cmd->name++;
	}
	cmd->argc = tokenCount;
	return cmd;
}


vector <command> commands_parser(char *get_input)
{
	int cmd_counts = 0;
	char *copied = get_input;

	vector<command> commands;

	while (*copied != '\0') {
		if (*copied == '|')
			cmd_counts++;
		copied++;
	}
	cmd_counts++;

	int i = 0;
	char *token;
	char *saveRecursivePtr;
	
	token = strtok_r(get_input, "|", &saveRecursivePtr);
	while (token != NULL && i < cmd_counts) {
		commands.push_back(*command_parser(token));
		token = strtok_r(NULL, "|", &saveRecursivePtr);
	}

	return commands;
}

std::string _rc_read(std::string fileName){

	std::ifstream fin;
    fin.open(fileName); 
    int i=0;
    std::string s="";
    std::string line;
    // Execute a loop until EOF (End of File) 
    while (getline(fin, line)) {
        //i++;
        //cout<<i<<":";
        //cout << line<<endl; 
        s+=line;
        s+='?';
}
   fin.close();
   return s;
}

char** rc_parser(){

	std::string s=_rc_read("shellrc");
		
	char* token;
	int i=0;
   token = strtok((char*)s.c_str(),"?");
    while (token != NULL) {
        //std::cout<<token<<std::endl;
        read_file[i++]=token;
        token = strtok(NULL, "?");
    }
    return read_file;
}

void set_my_env(){

	char** read_rc = rc_parser();

	prompt=read_file[0]
	path= read_rc[7];
	path+=5;
	//std::cout<<path;
	home= read_rc[4];
	home+=5;
	hostname= read_rc[6];
	hostname+=9;
	user= read_rc[1];
	user+=6;
	shell=read_rc[5];
	shell+=6;
	setenv("HOME",home,1);
	setenv("PATH",path,1);
	setenv("USER",user,1);
	setenv("SHELL",path,1);

	


}
