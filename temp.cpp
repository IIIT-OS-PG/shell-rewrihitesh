// written on 2 sep 2:30am 
// @uthor rewrihitesh

#include "in.h"
// #include <vector>
using std::vector;	

void close_pipes(int (*pipes)[2], int pipe_count);

vector <command> commands_parser(char *input);

int exec_commands(vector <command> cmds);

int exec_command(command cmd, int (*pipes)[2],int pipe_count);

command *command_parser(char *input)
{
	int tokenCount = 0;
	char *token;
	/* 
	allocate memory for the cmd structure 

	calloc creates memory and intilize it zero

	calloc creates ARG_MAX_COUNT -> number of blocks

	*/
	command *cmd = (command *)malloc(sizeof(command) +
				     ARG_MAX_COUNT * sizeof(char *));


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
	if(cmd->argv[0][0] == '"' || cmd->argv[0][0] == '\'' ){
		cmd->name++;
	}
	cmd->argc = tokenCount;
	return cmd;
}


vector <command> commands_parser(char *input)
{
	int cmd_counts = 0;
	int i = 0;
	char *token;
	char *saveptr;
	char *c = input;
	//commands *cmds;

	vector<command> commands;

	while (*c != '\0') {
		if (*c == '|')
			cmd_counts++;
		c++;
	}
	cmd_counts++;

	// cmds = (commands*)malloc(sizeof(commands) +
	// 	      cmd_counts * sizeof(command *));

	// if (cmds == NULL) {
	// 	fprintf(stderr, "error: memory allocation error\n");
	// 	exit(-1);
	// }

	token = strtok_r(input, "|", &saveptr);
	while (token != NULL && i < cmd_counts) {
		commands.push_back(*command_parser(token));
		token = strtok_r(NULL, "|", &saveptr);
	}

	//cmds->cmd_count = cmd_counts;
	return commands;
}


int main(int argc, char const *argv[])
{		
	vector <command> cmd;
	char* g = _input();
	cmd = commands_parser(g);

	exec_commands(cmd);

	return 0;
}


int exec_commands(vector <command> cmds)
{
	int exec_ret;

	if (cmds.size() == 1) {
		cmds[0].fds[STDIN_FILENO] = STDIN_FILENO;
		cmds[0].fds[STDOUT_FILENO] = STDOUT_FILENO;
		exec_ret = exec_command(cmds[0], NULL , cmds.size());
		wait(NULL);
	} else {
		/* execute a pipeline */
		int pipe_count = cmds.size() - 1;
		/* if any command in the pipeline is a built-in, raise error */
		int i;

		/* allocate an array of pipes. Each member is array[2] */
		int (*pipes)[2] =(int(*)[2]) calloc(pipe_count * sizeof(int[2]), 1);

		if (pipes == NULL) {
			fprintf(stderr, "error: memory alloc error\n");
			return 0;
		}


		/* create pipes and set file descriptors on commands */
		cmds[0].fds[STDIN_FILENO] = STDIN_FILENO;
		for (i = 1; i < cmds.size(); i++) {
			pipe(pipes[i-1]);
			cmds[i-1].fds[STDOUT_FILENO] = pipes[i-1][1];
			cmds[i].fds[STDIN_FILENO] = pipes[i-1][0];
		}
		cmds[pipe_count].fds[STDOUT_FILENO] = STDOUT_FILENO;

		/* execute the commands */
		for (i = 0; i < cmds.size(); i++)
			exec_ret = exec_command(cmds[i], pipes,cmds.size());

		close_pipes(pipes, pipe_count);

		/* wait for children to finish */
		//for (i = 0; i < cmds.size(); ++i)
			wait(NULL);
			wait(NULL);

		free(pipes);
	}

	return exec_ret;
}

int exec_command(command cmd, int (*pipes)[2],int pipe_count)
{
	// if (check_built_in(cmd) == 1)
	// 	return handle_built_in(cmds, cmd);

	pid_t child_pid = fork();

	if (child_pid == -1) {
		fprintf(stderr, "error: fork error\n");
		return 0;
	}

	/* in the child */
	if (child_pid == 0) {

		int input_fd = cmd.fds[0];
		int output_fd = cmd.fds[1];

		// change input/output file descriptors if they aren't standard
		// if (input_fd != -1 && input_fd != STDIN_FILENO)
			
			close(cmd.fds[0]);

			dup2(input_fd, STDIN_FILENO);

			close(cmd.fds[1]);

		// if (output_fd != -1 && output_fd != STDOUT_FILENO)
			
			dup2(output_fd, STDOUT_FILENO);

			close(cmd.fds[1]);

		// if (pipes != NULL) {

		// 	close_pipes(pipes, pipe_count);
		// }

		/* execute the command */
		execvp(cmd.name, cmd.argv);
		printf("%s\n",*(cmd.argv+1));

		/* execv returns only if an error occurs */
		fprintf(stderr, "error: %s\n", strerror(errno));

		/* cleanup in the child to avoid memory leaks */
		free(pipes);
		//free(input);
		//cleanup_commands(cmds);

		// if (parent_cmd != NULL) {
		// 	free(parent_cmd);
		// 	free(temp_line);
		// 	free(parent_cmds);
		// }


		/* exit from child so that the parent can handle the scenario*/
		_exit(EXIT_FAILURE);
	}
	/* parent continues here */
	return child_pid;
}

void close_pipes(int (*pipes)[2], int pipe_count)
{
	int i;

//fprintf(stderr, "error");

	for (i = 0; i < pipe_count; i++) {
		close(pipes[i][0]);
		close(pipes[i][1]);
	}

}