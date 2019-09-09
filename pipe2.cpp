#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
//#include "ourhdr.h"
#include <cstring>
//#include<string>
//#include<stdio.h>
#include <iostream>
using namespace std;
#define MAXLINE 55
int main(void)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;
    FILE *fpin, *fpout;
    printf("%% ");
    char s1[455];
    char s2[4556];
    char readbuf[80];
    while(1){
   fgets(s1, MAXLINE, stdin);
    fgets(s2, MAXLINE, stdin);
    if ((fpin=popen(s1,"r"))== NULL)
        printf("can't open");
    if ((fpout=popen(s2,"w"))== NULL)
        printf("can't open");
    while(fgets(readbuf, 80, fpin))
        fputs(readbuf, fpout);
    if(pclose(fpin) == -1)
            printf("plcose error");
    if(pclose(fpout) == -1)
            printf("plcose error");
    printf("%% ");
}
}