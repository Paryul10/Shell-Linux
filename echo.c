#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"echo.h"

void echo(char *dump)
{
	//printf("%s\n",dump);
    char *s=(char *)malloc(sizeof(char)*1024);
	int i=5,l=0;
	int j=0;
	while(dump[i]!='\n')           //reading after 'echo ', into s
		s[j++]=dump[i++];
	s[j]='\0';
    i=0;
    if(j==0)
	{
		printf("\n");
		return ;
	}
    char *token;
	//printf("%s\n",s);
	token = strtok(s," ");
	//printf("token=%s",token);
	while( token != NULL ) 
	{
		if(token[0]=='$')
		{
			//printf("yeya\n");
			char * p = getenv(token+1);
			//printf("%s\n",token+1);
			//printf("%s\n",p);
			if(p!=NULL) 
			{
				//printf("jidosj\n");
				printf("%s",p);
			}
			printf("\n");
			return;
		}
		else
		{
			for(int k=0;k<strlen(token);k++)
			{
				if(token[k]!='"') printf("%c",token[k]);
			}
			token = strtok(NULL," ");
			printf(" ");
		}
	}
	free(s);
	printf("\n");
  	
}