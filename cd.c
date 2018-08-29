#include <stdio.h>
#include <string.h>
//#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>

#include "cd.h"

void cd(char *token, char* home_dir)
{
	char del[]=" \n\t\r"; //these are characters which need to be skipped. like decompressed
	token=strtok(NULL,del);
	if(token==NULL)
		chdir(home_dir);
	else if((strcmp(token,"~"))==0)
		chdir(home_dir);
    else if(strstr(token,"~") && strlen(token)>1)
    {
        char * rem =(char *)malloc(sizeof(char)*1024);
        int len2 = strlen(token);
        int len1 = strlen("~");
        int len3 = strlen(home_dir);
        strcpy(rem,home_dir);
        for(int j=len3;j<len2+len3;j++)
        {
            rem[j]=token[j-len3+1];
        }
        rem[len2+len3]='\0';   //Padding with '\0' is very important

        if(chdir(rem)!=0)
        {
            printf("directory doesn't exist\n");
        }
        

    }
	else if(chdir(token)!=0)
		printf("directory doesn't exist\n");
}