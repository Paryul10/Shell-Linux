#include <stdio.h>
#include <sys/utsname.h> // to include uname , 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cd.h"
#include "pwd.h"
#include "echo.h"
#include "ls.h"
#include "foreground.h"
#include "variables.h"
#include "background.h"
#include "pinfo.h"


char home_dir[3][1024];

char homee[1024];
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
            int len1 = strlen(home_dir[2]);                    //chote wale ka length
            int len2 = strlen(cwd);
            char * rem =(char *)malloc(sizeof(char)*(len2-len1+1));

            for(int j=len1;j<len2;j++)
            {
                rem[j-len1]=cwd[j];
            }
            rem[len2-len1] = '\0';
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

/*void sig_handle(int sign)
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
void child_sig(int signo)
{
	pid_t pid;
	int r;
	pid=waitpid(WAIT_ANY,&r, WNOHANG);
	int i;
	for(i=0;i<back_c;i++)
	{
		if(background[i].pi==pid && background[i].state==1)
		{
			background[i].state=0;
			printf("\n%s %d exited normally\n",background[i].name,background[i].pi);
			
            // char * p=strstr(cwd,homee);      //strstr returns the pointer is arg[1] is found in arg[0] , this pointer points to the first occurence of arg[1]
            //                                        // if not found it will return null.
        
	        // if(strcmp(homee,cwd)==0)
	        // 	printf("<%s%s@%s%s:~>","\x1B[1;34m",uinfo.nodename,uinfo.sysname,"\x1B[0m");
	        // else 
            // {
            //     if(p)
            //     {   
            //         //converting ~ to absolute path.
            //         int len1 = strlen(homee);                     //chote wale ka length
            //         int len2 = strlen(cwd);
            //         char * rem =(char *)malloc(sizeof(char)*1024);
        
            //         for(int j=len1;j<len2;j++)
            //         {
            //             rem[j-len1]=cwd[j];
            //         }
            //         rem[len2] = '\0';
            //         printf("<%s%s@%s%s:~%s%s%s>","\x1B[1;34m",uinfo.nodename,uinfo.sysname,"\x1B[0m","\x1B[1;32m",rem,"\x1B[0m");
            //         free(rem);
                    
            //     }
            //     else
            //     {
            //         printf("<%s%s@%s%s:~%s%s%s>","\x1B[1;34m",uinfo.nodename,uinfo.sysname,"\x1B[0m","\x1B[1;32m",cwd,"\x1B[0m");
            //     }
            // }
	        // free(cwd);
            display(home_dir);
			fflush(stdout);
			//printf("\n");
            break;
            
		}
	}
	signal(SIGCHLD, child_sig);
	return;
}

int main()
{

    // int p = uname(&uinfo); // Might check return value here (non-0 = failure)
    // printf("%d",p);
    struct passwd *home;                //data structure containing user account information 
    uname(&uinfo);
    

    char *cwd=(char *)malloc(sizeof(char)*1024);
	cwd=getcwd(cwd,1024);

    strcpy(home_dir[0],uinfo.nodename); // copy the node name, host name and cwd because we need to use them
	strcpy(home_dir[1],uinfo.sysname);
    strcpy(home_dir[2],cwd);
    strcpy(homee,home_dir[2]);
    display(home_dir);

	free(cwd);
    // signal(SIGINT,SIG_IGN);
	// signal(SIGINT,sig_handle);
	signal(SIGCHLD,SIG_IGN);
	signal(SIGCHLD,child_sig);
	// signal(SIGTSTP,SIG_IGN);
	// signal(SIGTSTP,sig_handle);
	// signal(SIGQUIT,SIG_IGN);
	// signal(SIGQUIT,sig_handle);
    
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
			int flag = 0;
			if(strcmp(token,"quit")==0)
            {   
                flag=1;
				return 0;
            }
            else if(strcmp(token,"cd")==0)
            {
                flag = 1;
				cd(token,home_dir[2]);
            }
            else if(strcmp(token,"pwd")==0)
            {
                flag = 1;
				pwd();
            }
            else if(strcmp(token,"echo")==0)
			{
                flag = 1;
                echo(token);
            }
            else if(strcmp(token,"ls")==0)
            {
                flag = 1;
                ls(token);
            }
            else if((strcmp(token,"pinfo"))==0)
            {
                flag = 1;
                int len = strlen(home_dir[2]);
				pinfo(token,len,home_dir[2]);
            }
            else
            {
                int cnt=0;
                while(token!=NULL)
                {
                    strcpy(st[cnt++],token);
                    token = strtok(NULL," \n\t\r");
                }
                if((strcmp(st[0],"kjob"))==0)
                {
                    flag = 1;
                    continue;
					//kjob(st);
                }
				else if((strcmp(st[0],"fg"))==0)
                {   
                    flag = 1;
                    continue;
					//fg(st);
                }
				else if(strcmp(st[cnt-1],"&")==0)
				{
                    flag = 1;
					background_proc(st,cnt);
                    
				}
				else
				{
                    flag = 1;
					foreground(st,cnt);
				}
                  
            }
            
            if(flag==0)
            {printf("COMMNAND DOES NOT EXIST!!! %sUNGLI MAT KAR%s\n","\x1B[0;33m","\x1B[0m");}

            
            i++;
        }
        display(home_dir);
        free(buf2);
    }


}