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

void printlong(char *file,char *ch)
{
	struct stat fileStat;
	struct group *grp;
	struct passwd *pwd;
	char f[200];
	strcpy(f,file);
	strcat(f,"/");
	strcat(f,ch);
	if(stat(f,&fileStat) < 0)    
		return;
	grp=getgrgid(fileStat.st_gid);
	pwd=getpwuid(fileStat.st_uid);
	printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
	printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
	printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
	printf(" ");
	printf("%ld ",fileStat.st_nlink);
	printf("%s ",pwd->pw_name);
	printf("%s",grp->gr_name);
	printf(" %ld\t",fileStat.st_size);
	printf(" %.16s ",ctime(&fileStat.st_mtime) );
	printf("%s\n",ch);
}
void print_a(char file[],char c)
{
	int n,i;
	struct dirent **namelist;
	n=scandir(file,&namelist,NULL,alphasort);
	if (c=='s')
	{
		for(i=0;i<n;i++)
			printf("%s\t",namelist[i]->d_name );
		printf("\n");
	}
	else
		for(i=0;i<n;i++)
			printlong(file,namelist[i]->d_name);

}
void print_b(char file[],char c)
{
	int n,i=0;
	struct dirent **namelist;
	n=scandir(file,&namelist,NULL,alphasort);
	if (c=='s')
	{
		for(i=0;i<n;i++)
			if(namelist[i]->d_name[0]!='.')
				printf("%s\t",namelist[i]->d_name );
		printf("\n");
	}
	else
		for(i=0;i<n;i++)
			if(namelist[i]->d_name[0]!='.')
				printlong(file,namelist[i]->d_name);

}

void ls(char* token)
{
	token=strtok(NULL," \t\r\n");
	if(token==NULL )
	{
		print_b(".",'s');
	}
	else if(((strcmp(token,"-al"))==0) || ((strcmp(token,"-la"))==0))
	{
		token=strtok(NULL," \t\r\n");
		if(token==NULL)
			print_a(".",'l');
		else print_a(token,'l');
	}
	else if((strcmp(token,"-a")==0))
	{
		token=strtok(NULL," \t\r\n");
		if(token==NULL)
			print_a(".",'s');
		else if(strcmp(token,"-l")==0)
		{
			token=strtok(NULL," \t\r\n");
			if(token==NULL)
				print_a(".",'l');
			else print_a(token,'l');
		}
		else print_a(token,'s');
	}
	else if((strcmp(token,"-l")==0))
	{
		token=strtok(NULL," \t\r\n");
		if(token==NULL)
			print_b(".",'l');
		else if(strcmp(token,"-a")==0)
		{
			token=strtok(NULL," \t\r\n");
			if(token==NULL)
				print_a(".",'l');
			else print_a(token,'l');
		}
		else print_b(token,'l');
	}
	else 
	{
		print_b(token,'s');
	}
}
