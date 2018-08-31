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

#include "clock.h"

void clocks(char * token)
{

    char str[100][100];
    int i=0;
    while(token!=NULL)
    {
        strcpy(str[i++],token);
        token = strtok(NULL, " \n\t\r");
    }
    int interval=atoi(str[2]);
    char rtc[] = "/sys/class/rtc/rtc0/";
    char date[1000];
    strcpy(date,rtc);
    strcat(date,"date");
    char times[1000];
    strcpy(times,rtc);
    strcat(times,"time");
    while(1)
    {
        FILE *fp1;
        fp1=fopen(date,"r");
        char date_info[100];
        fgets(date_info,sizeof date,fp1);
        date_info[strlen(date_info)-1] = '\0';
        printf("%s",date_info);
        fclose(fp1);
        FILE *fp2;
        fp2=fopen(times,"r");
        char time_info[100];
        fgets(time_info,sizeof date,fp2);
        printf(" %s",time_info);
        fclose(fp2);
        sleep(interval);
    }
}