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
#include "variables.h"
#include "clock.h"
/*char home_dir[3][1024];

char homee[1024];
struct utsname uinfo;

void sig_handle(int sign)
{
	if (sign==2 ||sign==3)
	{
		fflush(stdout);
		printf("\n");
		char home_dir[3][500];
		strcpy(home_dir[0],uinfo.nodename);
		strcpy(home_dir[1],uinfo.sysname);
		char *cwd=(char *)malloc(sizeof(char)*1024);
		cwd=getcwd(cwd,1024);
		free(cwd);
		strcpy(home_dir[2],cwd);		
		signal(SIGQUIT,sig_handle);
		signal(SIGINT,sig_handle);
		
	}
		if(sign == 20)
			kill(curid,SIGTSTP);
	
	return;
}*/

void clocks(char * token)
{
    // struct passwd *home;                //data structure containing user account information 
    // uname(&uinfo);
    

    // char *cwd=(char *)malloc(sizeof(char)*1024);
	// cwd=getcwd(cwd,1024);

    // strcpy(home_dir[0],uinfo.nodename); // copy the node name, host name and cwd because we need to use them
	// strcpy(home_dir[1],uinfo.sysname);
    // strcpy(home_dir[2],cwd);
    // strcpy(homee,home_dir[2]);

    //signal(SIGTSTP, handler);

    //signal(SIGINT, handle_sigint);
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
    long long int count = 0;
    while(count <= atoi(str[4]))
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
        count += interval;
        // signal(SIGINT,SIG_IGN);
	    // signal(SIGINT,sig_handle);
	    // signal(SIGTSTP,SIG_IGN);
	    // signal(SIGTSTP,sig_handle);
	    // signal(SIGQUIT,SIG_IGN);
	    // signal(SIGQUIT,sig_handle);
    }
}