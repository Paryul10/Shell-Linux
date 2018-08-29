#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pwd.h"

void pwd()
{
	char *cwd=(char *)malloc(sizeof(char)*1024);
	cwd=getcwd(cwd,1024);
	printf("%s\n",getcwd(cwd,1024));
	free(cwd);	
	return;
}