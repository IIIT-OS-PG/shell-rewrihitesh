#include "parser.h"
#include "rc.h"

int handle_special_cmd(command *cmd);

char *oldpwd;

int main(){

	set_my_env();

	pid_t child_pid,parent_pid;

	int process_status;

	char buf[500];

	std::string shell_prompt = getPrompt();

while(1){
	std::cout<<shell_prompt<<":"<<getcwd(buf,500);
	char* g = _input();
	if(g==NULL){printf("\n");exit(0);}// if ctrl+d is presses just exit from the 
	if(isEmpty(g)){free(g);continue;} /* if input is /n just return the prompt*/
	
	command *cmd;		
	cmd = command_parser(g);

	if(handle_special_cmd(cmd))
		continue;

	child_pid = fork();

	if(child_pid==0){
		if(execvp(cmd->name,cmd->argv)<0){
			printf("No such command\n");
			exit(-1);
		}
	}else{
			waitpid(child_pid, &process_status, WUNTRACED);
	}

	free(cmd);
	free(g);
}	
	return 0;
}

int handle_special_cmd(command *cmd){

	int flag;

	char buffer[2048];

	if(strcmp(cmd->name,"exit")==0)
		exit(-1);

	if (strcmp(cmd->name, "cd") == 0) {	// declare in <unistd.h>
				
		if(strcmp(cmd->argv[1],"-")==0){
			if(oldpwd == NULL){
				fprintf(stderr, "error OLDPWD is not set \n"); return 1;}
				flag = chdir(oldpwd);
				printf("%s\n",getcwd(buffer,sizeof(buffer)));
		}else{
			oldpwd = getcwd(buffer,sizeof(buffer));
			flag = chdir(cmd->argv[1]);		// changes the current working directory of the calling process
		}
			
											// more function are getcwd, getwd, get_current_dir_name
 											//to the directory specified in path.

		if(strcmp(cmd->argv[1],"~")==0){
				flag = chdir(home);

			}	

		if (flag != 0) {
			fprintf(stderr, "error: unable to change dir\n");
			return 0;
		}
		return 1;
	}

	return 0;
}


/*
			--------Gyan--------

Calling perror will give you the interpreted value of errno, 
which is a thread-local error value written to by POSIX syscalls
(i.e., every thread has it's own value for errno). 
For instance, if you made a call to open(),
 and there was an error generated (i.e., it returned -1), 
 you could then call perror immediately afterwards to see what the actual error was. 

 fprintf(stderr, ...) on the other-hand can be used to print your own custom error messages. 
 By printing to stderr, you avoid your error reporting output being mixed with 
 "normal" output that should be going to stdout.

 */