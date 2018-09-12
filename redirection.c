#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include "redirection.h"

void redirect(char * s,int type)
{
    char * or[10];
    char * ir[10];
    char * proc[10];
    char * token;
    int inp,out;

    int fr=0;
    token = strtok(s,">");
    while(token != NULL)                      // commands seperated by forward redirections;
    {
        or[fr] = token;
        token = strtok(NULL,">");
        fr++;
    }
    or[fr] = '\0';

    /*int k=0;
    while(k<fr)
    {
        printf("%d , %s\n",k,or[k]);
        k++;
    }*/
    
    int br=0;
    token = strtok(or[0],"<");
    while(token != NULL)                      // commands seperated by backward redirections;
    {
        ir[br] = token;
        token = strtok(NULL,"<");
        br++;
    }
    ir[br] = '\0';

    /*k=0;
    while(k<fr)
    {
        printf("%d , %s\n",k,ir[k]);
        k++;
    }*/

    int i=0;
    token = strtok(ir[0]," \n\t\r");
    while(token != NULL)                      // commands seperated by backward redirections;
    {
        proc[i] = token;
        token = strtok(NULL," \n\t\r");
        i++;
    }
    proc[i] = '\0';

    /*int k=0;
    while(k<i)
    {
        printf("%d , %s\n",k,proc[k]);
        k++;
    }*/

    //printf("YEA\n");

    char * new_tok;
    int pid;
    pid=fork();
    if(ir[1]!=NULL)
    {
        new_tok=strtok(ir[1]," \n\t\r");
        if(new_tok!=NULL)
        {
            inp = open(new_tok,O_RDONLY);
            if(inp<0 && pid==0)
            {
                printf("FILE DOES NOT EXIST!!\n");
                return;
            }
            if(pid==0 && inp>0) dup2(inp,0);
        }
        else
        {
            if(pid == 0)
            {
                printf("INVALID INPUT FILE\n");
                exit(0);
            }
        }
    }

    char * new_tok2;
    if(or[1]!=NULL)
    {
        new_tok2=strtok(or[1]," \n\t\r");
        if(new_tok2!=NULL)
        {
            if(type==1)
            {
                out = open(new_tok2,O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
            }
            if(type==2)
            {
                out = open(new_tok2,O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
            }
            if(pid==0)
            {
                dup2(out,1);
            }
        }
        else
        {
            if(pid == 0)
            {
                printf("INVALID OUTPUT FILE\n");
                exit(0);
            }
        }
    }
    int status;
    if(pid==0)
    {
        execvp(proc[0],proc);
        exit(0);
    }
    else
    {
        while(wait(&status)!=pid);
    }
    close(inp);
    close(out);
    return;
}