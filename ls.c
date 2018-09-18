#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "ls.h"

void printlong(char *file,int k,char * ch)
{
	char f[200]; // create the path which is to be taken to evaluate
	strcpy(f,file);
	strcat(f,"/");
	strcat(f,ch);

	struct stat info_file;
	if(stat(f,&info_file) < 0)    
		return;

	struct group *grp;
	struct passwd *pass;
	pass=getpwuid(info_file.st_uid);
	grp=getgrgid(info_file.st_gid);

	if(k==1)    // if the file / directory exists
	{
		printf( (S_ISDIR(info_file.st_mode)) ? "d" : "-");
		printf( (info_file.st_mode & S_IRUSR) ? "r" : "-");
		printf( (info_file.st_mode & S_IWUSR) ? "w" : "-");
		printf( (info_file.st_mode & S_IXUSR) ? "x" : "-");
		printf( (info_file.st_mode & S_IRGRP) ? "r" : "-");
		printf( (info_file.st_mode & S_IWGRP) ? "w" : "-");
		printf( (info_file.st_mode & S_IXGRP) ? "x" : "-");
		printf( (info_file.st_mode & S_IROTH) ? "r" : "-");
		printf( (info_file.st_mode & S_IWOTH) ? "w" : "-");
		printf( (info_file.st_mode & S_IXOTH) ? "x" : "-");
		printf(" ");
		printf("%ld ",info_file.st_nlink);
		printf("%s ",pass->pw_name);
		printf("%s",grp->gr_name);
		printf(" %ld\t",info_file.st_size);
		printf(" %.s ",ctime(&info_file.st_mtime) );
		printf("%s\n",ch);
	}
}

void check_b(char file_name[], char * d, char c)
{
	int n,i=0;
	struct dirent **namelist;
	
	n=scandir(file_name,&namelist,NULL,alphasort);
	if (c=='s')
	{
		i=0;
		while(i<n)
		{
			if(namelist[i]->d_name[0]!='.')
				printf("%s\t",namelist[i]->d_name );

			i++;
		}
		printf("\n");
	}
	else
	{
		i=0;
		while(i<n)
		{
			if(namelist[i]->d_name[0]!='.')
				printlong(file_name,1,namelist[i]->d_name);
			i++;
		}
	}

}




void check_a(char file[],char  * d,char c)
{
	int n,i;
	struct dirent **namelist;
	n=scandir(file,&namelist,NULL,alphasort);
	if (c=='s')
	{
		i=0;
		while(i<n)
		{
			printf("%s\t",namelist[i]->d_name );
			i++;
		}
		printf("\n");
	}
	else
	{
		i=0;
		while(i<n)
		{
			printlong(file,1,namelist[i]->d_name);
			i++;
		}
	}

}




void print_b(char c,int k,char file_name[])
{
	int n,i=0;
	struct dirent **namelist;
	if(k!=1)
	{
		printf("Error passing arguments");
	}
	n=scandir(file_name,&namelist,NULL,alphasort);
	if (c=='s')
	{
		i=0;
		while(i<n)
		{
			if(namelist[i]->d_name[0]!='.')
				printf("%s\t",namelist[i]->d_name );

			i++;
		}
		printf("\n");
	}
	else
	{
		i=0;
		while(i<n)
		{
			if(namelist[i]->d_name[0]!='.')
				printlong(file_name,1,namelist[i]->d_name);
			i++;
		}
	}

}


void print_a(char file[],char c,int k)
{
	int n,i;
	struct dirent **namelist;
	n=scandir(file,&namelist,NULL,alphasort);
	if(k!=1)
	{
		printf("Error passing arguments");
	}
	if (c=='s')
	{
		i=0;
		while(i<n)
		{
			printf("%s\t",namelist[i]->d_name );
			i++;
		}
		printf("\n");
	}
	else
	{
		i=0;
		while(i<n)
		{
			printlong(file,1,namelist[i]->d_name);
			i++;
		}
	}

}


void ls(char* tok)
{
	tok=strtok(NULL," \t\r\n");
	if(tok==NULL )
	{
		print_b('s',1,".");
	}
	else if((strcmp(tok,"-a")==0))
	{
		tok=strtok(NULL," \t\r\n");
		if(tok==NULL)
			print_a(".",'s',1);
		else if(strcmp(tok,"-l")==0)
		{
			tok=strtok(NULL," \t\r\n");
			if(tok==NULL)
				print_a(".",'l',1);
			else print_a(tok,'l',1);
		}
		else print_a(tok,'s',1);
	}
	else if(((strcmp(tok,"-la"))==0)  ||  ((strcmp(tok,"-al"))==0))
	{
		tok=strtok(NULL," \t\r\n");

		if(tok !=NULL)
		{
			print_a(tok,'l',1);	
		}
		else
		{
			print_a(".",'l',1);
		}
	}
	else if((strcmp(tok,"-l")==0))
	{
		tok=strtok(NULL," \t\r\n");
		if(tok==NULL)
			print_b('l',1,".");
		else if(strcmp(tok,"-a")==0)
		{
			tok=strtok(NULL," \t\r\n");
			if(tok==NULL)
				print_a(".",'l',1);
			else print_a(tok,'l',1);
		}
		else print_b('l',1,tok);
	}
	else 
	{
		print_b('s',1,tok);
	}
}
