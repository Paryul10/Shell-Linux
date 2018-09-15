#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "background.h"
#include "variables.h"
#include "background.h"

void background_proc(char st[][100],int cnt)
{
    char * argv[cnt+1];
    argv[cnt] = NULL;
    for(int i =0;i<cnt;i++)
    {
        argv[i] = st[i];
    }
    int pid = fork();
    if (pid < 0)
    {
        printf("Fork Failed\n");
        return;
    }
    else if (pid==0)
    {
        execvp(argv[0],argv);
    }
    else
    {
        printf("pid : %d\n",pid);
    }

    back_c++;
    //STORING THE NAME THE COMMAND WHICH WAS EXECUTED TO BE PRINTED LATER
    background[back_c].pi=pid;
    background[back_c].state=1;
    char temp[200];
    strcpy(temp,argv[0]);
    int x=1;
    while(x<cnt-1){
    strcat(temp," ");
    strcat(temp,st[x++]);
    }
    strcpy(background[back_c].name,temp);
    
    return;

}