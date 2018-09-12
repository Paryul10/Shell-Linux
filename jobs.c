#include "header.h"
#include "variables.h"
#include "jobs.h"
void print_jobs()
{
	int i,j=1;
	for (i = 0; i <back_c ; i++)
		if(background[i].state == 1 && background[i].pi>0)
        {
			printf("[%d] %s %s [%d]\n",j++,background[i].name,"Running",background[i].pi);
        }
        if(background[i].state == 0 && background[i].pi>0)
        {
			printf("[%d] %s %s [%d]\n",j++,background[i].name,"Stopped",background[i].pi);
        }
}
