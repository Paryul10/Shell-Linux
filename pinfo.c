#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/resource.h>
#include "pinfo.h"

/*void pinfo(char * token)
{
    struct stat sts;    
    token=strtok(NULL," ");
    if(token == NULL)
    {
        int pid = getpid();
        printf("pid--%d\n",pid);
        char buffer[40];
        sprintf(buffer,"%d",pid);           //sprintf stores the info in buffer info = pid here
        char str1[] ="/proc/";
        strcat(str1,buffer);                // str1 = /proc/pid
        char execute[1000];
		char exec[1000];
        strcpy(execute,str1);               // execute = /proc/pid
		strcat(execute,"/exe");             // execute = /proc/pid/exe
		char str2[]="/status";
        strcat(str1,str2);                  // str1 = /proc/pid/status
        FILE *file = fopen(str1, "r");
        int count = 0;
        struct rusage usage;                //to get resource usage
        readlink(execute,exec,1000);        // readlink puts the content of symlink path in exec , 1000 is size of exec (buffer).
        getrusage(RUSAGE_SELF,&usage);
        if(file != NULL)
        {
            char line[1024];
            while(fgets(line,sizeof line , file) != NULL)        // read line from the status 
            {
                if(count == 2)
                {
                    printf("%s",line);
                    break;
                }
                else
                {
                    count++;
                }
            }
            // int piid;
            // char runstatus;
            // long unsigned int mem;
            // fscanf(file,"%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",&piid,&runstatus,&mem); 
            printf("Virtual Memory--%ld\n",usage.ru_maxrss);
            printf("Executable Path--%s\n",exec);
            fclose(file);
        }
        else
        {
            printf("FILE DOES NOT EXIST\n");
        }
    }
    else
	{
		char str3[]="/proc/";
		char execute[1000],exec[1000];
        //printf("%s\n",token);
		strcat(str3,token);
        char str5[strlen(str3)-1];
        for(int i=0;i<strlen(str3)-1;i++)
        {
            str5[i] = str3[i];
        }
        str5[strlen(str3)-1] = '\0';
        // printf("%d",strlen(str3));
        // printf("%s\n",str5);
        // printf("%d\n",stat(str5,&sts));
		if(stat(str5, &sts) == -1 && errno == ENOENT) 
		{
			printf("invalid pid\n");
		}
		else
		{
			strcpy(execute,str5);
			strcat(execute,"/exe");
			printf("pid--%s",token);
			int lineNumber=2;
			char str4[]="/status";
			strcat(str5,str4);
			FILE *file = fopen(str5,"r");
			int count=0;
			struct rusage usage;
			readlink(execute,exec,1000);
			getrusage(RUSAGE_SELF,&usage);
			if ( file != NULL )
			{
				char line[1024]; /* or other suitable maximum line size */
				/*while (fgets(line, sizeof line, file) != NULL) /* read a line */
				/*{

					if (count == 2)
					{
						printf("%s",line);
						break;
						//in case of a return first close the file with "fclose(file);"
					}
					else
					{
						count++;
					}
				}
                // int piid;
                // char runstatus;
                // long unsigned int mem;
                // fscanf(file,"%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",&piid,&runstatus,&mem); 
				fclose(file);
				printf("Memory Usage-- %lu\n",usage.ru_maxrss);
				printf("Executable path-- %s\n",exec);

			}
			else
			{
				printf("file doesn't exist\n");
			}
		}
	}
	return;*/
//}

void pinfo(char * token,int homepathlength,char * home)
{
    char stat1[1000];
    char exec1[1000];
    int cnt = 1;
    token=strtok(NULL," ");
    //printf("breuofncd\n");
    if(token!=NULL)
    {
        //printf("breuofncd\n");
        cnt++;
    }
    if(cnt>1)
    {
        int l = strlen(token);
        //printf("%d\n",l);
        token[l-1] = '\0';
      strcpy(stat1,"/proc/");
    //   char buffer[40];
    //   sprintf(buffer,"%d",token);

      strcat(stat1,token);
      //printf("%s\n",token);
      strcat(stat1,"/stat");
      //printf("%s\n",stat1);
      strcpy(exec1,"/proc/");
      strcat(exec1,token);
      strcat(exec1,"/exe");
      //printf("%s\n",exec1);
    }
    else
    {
      sprintf(stat1,"/proc/%d/stat",getpid());      
      sprintf(exec1,"/proc/%d/exe",getpid());
    } 
    //printf()

    FILE *fp;
    if((fp=fopen(stat1,"r"))==NULL)
    {
      printf("Error: process doesn't exist\n");
    }
    else
    {
      char execname[1000];
      int pid;
      char runstatus;
      long unsigned int mem; 
      fscanf(fp,"%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",&pid,&runstatus,&mem);                       
      fclose(fp);
      printf("Process ID -- %d\n",pid);
      printf("Process Status -- %c\n",runstatus);
      printf("Memory -- %lu\n",mem);

      int a = readlink(exec1,execname,256);
      execname[a]='\0';
      
      //if(strstr(execname,home))

      /*if(a>=homepathlength)
      {
        int inhome=1;
        int i;
        for(i=0; i<homepathlength; i++)
        {
          if (execname[i]!=home[i])
          {
            inhome=0;
            break;
          }
        }

        if(inhome)
        {
          char final[1000];
          final[0]='~';
          for(i=homepathlength; i<a; i++)
          {
            final[i-homepathlength+1] = execname[i];
          }
          final[i-homepathlength+1]='\0';
          strcpy(execname,final);
        }

      }*/

        char *p;
        char *str = execname;
        char *orig = home;
        char *rep = "~";
        static char buffer[4096];
        if (p = strstr(str, orig))
        {
            strncpy(buffer, str, p - str);
            buffer[p - str] = '\0';
            sprintf(buffer + (p-str), "%s%s", rep, p + strlen(orig));
            strcpy(execname, buffer);
        }
        printf("Executable Path -- %s\n", execname);
    }  
}   
