// written on 2 sep 10pm 
// @uthor rewrihitesh

#define ARG_MAX_COUNT    1024      /* max number of arguments to a command */
#define HISTORY_MAXITEMS 100       /* max number of elements in the history */

/* Type declarations */
typedef struct com {		   /* a struct that stores a parsed command */
	int argc;                  /* number of arguments in the comand */
	char *name;                /* name of the command */
	char *argv[ARG_MAX_COUNT]; /* the arguments themselves */
	int fds[2];                /* the file descriptors for input/output */
	char special_case;			/* to handle some flags */
}command;

int check_for_built_in_cmd(command *cmd)
{
	return strcmp(cmd->name, "exit") == 0 ||
		strcmp(cmd->name, "cd") == 0 ||
		strcmp(cmd->name, "history") == 0;
}

