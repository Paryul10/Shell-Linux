#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <error.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>


#include "remindme.h"

void remindme(char * token)
{
    char str[100][100];
    int i=0;
    //strcpy(str[i],token);
    while(token!=NULL)
    {
        strcpy(str[i++],token);
        token = strtok(NULL," \n\t\r");
    }
    int pid = fork();

    if(pid < 0)
    {
        printf("FORK FAILED!!!\n");
    }
    else if(pid ==0)
    {
        sleep(atoi(str[1]));
        printf("\n REMINDER::");
        for(int j=2;j<i;j++)
        {
            printf("%s ",str[j]);
        }
        printf("\n");
        //kill(getpid(),SIGKILL);
        
    }
    else
    {
        return ;
    }
}