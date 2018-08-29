#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"echo.h"

void echo(char *dump)
{
    char *s=(char *)malloc(sizeof(char)*1024);
	int i=5,l=0;
	int j=0;
	while(dump[i]!='\n')           //reading after 'echo ', into s
		s[j++]=dump[i++];
    i=0;
    if(j==0)
	{
		printf("\n");
		return ;
	}
	s[j]='\0';
    char *token;
	//printf("%s\n",s);
	token = strtok(s," ");
	while( token != NULL ) 
	{
		//printf("%s ", token );
		for(int k=0;k<strlen(token);k++)
		{
			if(token[k]!='"') printf("%c",token[k]);
		}
		token = strtok(NULL," ");
		printf(" ");
	}
	free(s);
	printf("\n");
  	
}