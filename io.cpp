#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int check_redirection(char **args,int arg_count)
{
  for(int i=0;i<arg_count;i++)
  {
    if(!strcmp(args[i],">"))
    {
      return 1;
    }
    if(!strcmp(args[i],"<"))
    {
      return 2;
    }
    if(!strcmp(args[i],">>"))
    {
      return 3;
    }
    if(!strcmp(args[i],"<<"))
    {
      return 4;
    }
  }
  return 0;
} 

void io_redirection(char **args,int operation,int arg_count)
{
    int fd,fd2;
    int flag=0;
    char *filename=args[arg_count-1];
    // printf("%s%d\n",filename,arg_count);
	
    for(int i=0;i<arg_count;i++)
    {
      if(!strcmp(args[i],">"))
      {
        args[i]=NULL;
        break;
      }
      if(!strcmp(args[i],"<"))
      {
        args[i]=NULL;
        break;
      }
      if(!strcmp(args[i],">>"))
      {
        args[i]=NULL;
        break;
      }
      if(!strcmp(args[i],"<<"))
      {
        args[i]=NULL;
        break;
      }   
    }
    
  	pid_t pid = fork();  

    if (pid == -1) 
	{ 
        	perror("\nerror\n"); 
        	return; 
	} 
	else if (pid == 0) 
	{ 
    if(operation==1)
    {
  		if((fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
  		{
        	perror("open error");
        	
      }

      	dup2(fd, 1);
      	close(fd);
      	execvp(args[0], args);
      	perror("execvp error");
      	_exit(EXIT_FAILURE);    
    }
    else if(operation==2)
    {

      if((fd = open(filename,O_RDONLY, 0644)) < 0)
      {
          perror("open error");
          
      }

        dup2(fd, 0);
        close(fd);
        execvp(args[0], args);
        perror("execvp error");
        _exit(EXIT_FAILURE);    
       
    }
    else if(operation==3)
    {

      if((fd = open(filename, O_APPEND|O_CREAT | O_WRONLY, 0644)) < 0)
      {
          perror("open error");
          
      }

        dup2(fd, 1);
        close(fd);
        execvp(args[0], args);
        perror("execvp error");
        _exit(EXIT_FAILURE);    
        
    }
    else if(operation==4)
    {

      if((fd = open(filename, O_RDONLY, 0644)) < 0)
      {
          perror("open error");
          
      }
        dup2(fd, 0);
        close(fd);
        execvp(args[0], args);
        perror("execvp error");
        _exit(EXIT_FAILURE);    
    }

  }
	else 
	{  
	        wait(NULL);  
	        return ;
	} 
}
int main() 
{
  int arg_count=0;
  while(1)
  {
    
    char* args[1024];
    ssize_t bufsize=1024;
    char *inbuilt[1024]={"exit","cd","clear"};
    
    char *ptr;
    int i=0;  
    char *str;
    getline(&str,&bufsize,stdin);      
    ptr= strtok(str, " \n");
    while(ptr != NULL)
    {      
      args[i]=ptr;  
      ptr = strtok(NULL, " \n");
      i++;
    }
    arg_count=i;
    args[i]=NULL;

    int operation=check_redirection(args,arg_count);//1- (>) 2-(<) 3 - (>>) 4- (<<);
      io_redirection(args,operation,arg_count);
  } 
    return 0;
}
