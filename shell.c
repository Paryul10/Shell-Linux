#include <stdio.h>
#include <sys/utsname.h> // to include uname , 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cd.h"
#include "pwd.h"
#include "echo.h"

struct utsname uinfo; // define a utsname structure, get name and information about current kernel


void display(char home_dir[][1024])
{
    char *cwd=(char *)malloc(sizeof(char)*1024);
	cwd=getcwd(cwd,1024);


    char * p=strstr(cwd,home_dir[2]);      //strstr returns the pointer is arg[1] is found in arg[0] , this pointer points to the first occurence of arg[1]
                                           // if not found it will return null.

	if(strcmp(home_dir[2],cwd)==0)
		printf("<%s%s@%s%s:~>","\x1B[1;34m",uinfo.nodename,uinfo.sysname,"\x1B[0m");
	else 
    {
        if(p)
        {   
            //converting ~ to absolute path.
            int len1 = strlen(home_dir[2]);                     //chote wale ka length
            int len2 = strlen(cwd);
            char * rem =(char *)malloc(sizeof(char)*1024);

            for(int j=len1;j<len2;j++)
            {
                rem[j-len1]=cwd[j];
            }
            rem[len2] = '\0';
            printf("<%s%s@%s%s:~%s%s%s>","\x1B[1;34m",uinfo.nodename,uinfo.sysname,"\x1B[0m","\x1B[1;32m",rem,"\x1B[0m");
            free(rem);
            
        }
        else
        {
            printf("<%s%s@%s%s:~%s%s%s>","\x1B[1;34m",uinfo.nodename,uinfo.sysname,"\x1B[0m","\x1B[1;32m",cwd,"\x1B[0m");
        }
    }
	free(cwd);
	return ;
}

int main()
{
    // int p = uname(&uinfo); // Might check return value here (non-0 = failure)
    // printf("%d",p);
    struct passwd *home;                //data structure containing user account information 
    uname(&uinfo);
    char home_dir[3][1024];

    char *cwd=(char *)malloc(sizeof(char)*1024);
	cwd=getcwd(cwd,1024);

    strcpy(home_dir[0],uinfo.nodename); // copy the node name, host name and cwd because we need to use them
	strcpy(home_dir[1],uinfo.sysname);
    strcpy(home_dir[2],cwd);
    display(home_dir);

	free(cwd);
    
    while(1)
    {
        char *buf2,*buf;
		buf = (char *)malloc(sizeof(char)*1024);
		char *token;
		char *token_col[100];
		ssize_t size=0;
		getline(&buf2,&size,stdin);             // buf 2 reads the input. this is the syntax of getline..
		if(strcmp(buf2,"\n")==0)
		{
			display(home_dir);
			continue;
		}

        //strcpy(buf,buf2);
		int i=0,j=0;
		token_col[j]=strtok(buf2,";");            //We need a pointer to char to store tokens
                                                 //strtok -> it splits string on the basis of a delimiter. 
                                                //the above statement assigns token the first string obtained after splitting

        while(token_col[j]!=NULL)             //We need to run the loop until there are no tokens to return 
		{
			j++;                            // counts the total number of commands given   
			token_col[j]=strtok(NULL,";"); // syntax of strtok , i dont know.
                                          //since we need to store all the commands after spliting ,we use 2d-char array
		}

        while(i<j)                      // start executing command by command.
		{
			int k=0,cr=0,cp=0;
			char st[100][100];			
			char *temp=token_col[i];
            token=strtok(token_col[i]," \n\t\r");
			if(token==NULL)
			{
				i++;
				continue;
			}
			
			if(strcmp(token,"quit")==0)
				return 0;
            else if(strcmp(token,"cd")==0)
				cd(token,home_dir[2]);
            else if(strcmp(token,"pwd")==0)
				pwd();
            else if(strcmp(token,"echo")==0)
				echo(token);
            else
                printf("COMMNAND DOES NOT EXIST!!! %sUNGLI MAT KAR%s\n","\x1B[0;33m","\x1B[0m");

            
            i++;
        }
        display(home_dir);
        free(buf2);
    }


}