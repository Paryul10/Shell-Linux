#include "header.h"
#include "variables.h"
#include "jobs.h"
void print_jobs()
{
	int i,j=1;
	for (i = 1; i<=back_c ; i++)
    {
		if(background[i].state == 1 && background[i].pi>0)
        {
			printf("[%d]\t%s\t\t%s\t[%d]\n",j++,"Running",background[i].name,background[i].pi);
        }
        if(background[i].state == 0 && background[i].pi>0)
        {
			printf("[%d]\t%s\t\t%s\t[%d]\n",j++,"Stopped",background[i].name,background[i].pi);
        }
    }
}
