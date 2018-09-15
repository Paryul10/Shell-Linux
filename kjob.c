#include "header.h"
#include "variables.h"
#include "kjob.h"

void kjob(char info[][100])
{
    int job_no=atoi(info[1]);
    int signal_no=atoi(info[2]);
    
    printf("SENDING SIGNAL %d  TO JOB %d\n",signal_no,job_no);
    if(job_no > back_c)
    {
        printf("NO SUCH JOB NUMBER !! TRY AGAIN SWEETY!\n");
    }
    else
    {
        //background[job_no].state=0;
        if(background[job_no].state==1)
        {
            kill(background[job_no].pi,signal_no);
            background[job_no].state=0;
        }
        else
        {
            printf("STOPPED PROCESS\n");
        }
    }

}