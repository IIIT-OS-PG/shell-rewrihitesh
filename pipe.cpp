#include "parser.h"
#include "rc.h"

using namespace std;

pid_t p1, p2;

void exec_bitch(std::vector<command> v_cmds){
	// number of pipes in a program
	int pipecount = v_cmds.size()-1;

	int child_pid,file_discriptor_close=0,stat_loc,a=0;

	// array of fds
	int fd[2*pipecount];

	for(int i=0;i<pipecount;i++){
		if(pipe(fd + (i*2)) < 0) {
            fprintf(stderr, "ERROR:could not pipe\n");
            exit(-1);
        }
	}
	for(;a<pipecount+1;a++,file_discriptor_close+=2){

		child_pid = fork();

    if (child_pid == 0) {  

        if(a < pipecount){
                if(dup2(fd[file_discriptor_close + 1], STDOUT_FILENO) < 0){
                    fprintf(stderr, "erro in duplicating file");
                    exit(-1);
                }
            }
       
            int temp = 0;
            
            if(file_discriptor_close != 0 ){
                if(dup2(fd[file_discriptor_close-2], STDIN_FILENO) < 0){
                     fprintf(stderr, "erro in duplicating file");
                    exit(-1);
                }
            }
        for(;temp < 2*pipecount; temp++) close(fd[temp]);

        execvp(v_cmds[a].name, v_cmds[a].argv);
       
        fprintf(stderr, "No such command in the path");

     } else { 
     	
        /* parent code if any will go here*/

    	//fprintf(stderr, "unable to do fork\n");
        		 
    	} 
	}

	for(int i = 0; i < 2 * pipecount; i++){
        close(fd[i]);
    }
    for(int i = 0; i < pipecount + 1; i++){
        waitpid(child_pid, &stat_loc, 0);
    }   
}


int main(){

    std::vector<command> v_cmds;

    /*char* g = _input();

    v_cmds=commands_parser(g);*/

    //cout<<init_rc();

    string line;

    read_rc();  

    char a[5]={'a','b','c','d'};
    a[4]='\0';

    memmove (a, a+1, strlen (a+1) + 1);    

    //cout<<a;

    std::ifstream fin;

    fin.open("shellrc"); 
    int i=0;
    string s="";
    // Execute a loop until EOF (End of File) 
    while (getline(fin, line)) {
        //i++;
        //cout<<i<<":";
        //cout << line<<endl; 
        s+=line;
        s+='?';
}
   fin.close();
   //cout<<s;


   char* token;

   char* read_file[100];

   token = strtok((char*)s.c_str(),"?");
   i=0;
    while (token != NULL) {
        
        cout<<i++<<":";
        cout<<token<<endl;
        read_file[i]=token;

        token = strtok(NULL, "?");
    }

//    exec_bitch(v_cmds);  

	return 0;
}