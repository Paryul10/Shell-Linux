#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "foreground.h"
#include "variables.h"

void foreground(char st[][100],int cnt)
{
    char * argv[cnt+1];
    int i=0;
    int status;
    for(int k=0;k<cnt;k++)
    {
        argv[k] = st[k];
    }
    argv[cnt] = NULL;
    int pid = fork();
    if(pid < 0)
    {
        printf("Fork FAILED\n");
        return;
    }
    else if(pid==0)
    {
        execvp(argv[0],argv);
        printf("Command not FOUND!!\n");
        exit(0);
    }
    else
    {
        while(wait(&status)!=pid);
    }
    
    int x;
	curid=pid;
        
    if(WIFSTOPPED(x))
    {
        background[back_c].pi=pid;
        background[back_c].state=1;
        strcpy(background[back_c].name,argv[0]);
        back_c++;
    }
    else
    {
		background[back_c].pi=pid;
	    background[back_c].state=0;
		strcpy(background[back_c].name,argv[0]);
        back_c++;
    }
    return;

}