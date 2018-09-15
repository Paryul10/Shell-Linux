#include "header.h"
#include "variables.h"
#include "bg.h"

void bg(char st[][100])
{
    int job_no = atoi(st[1]);
    if (job_no > back_c)
    {
        printf("NO SUCH PROCESS EXISTS\n");
        return;
    }
    else if (background[job_no].state == 0)
    {
        background[job_no].state = 1;
        char *argv[10];
        char *token;
        token = strtok(background[job_no].name, " \n\t\r");
        int i = 0;
        while (token != NULL)
        {
            argv[i] = token;
            token = strtok(NULL, " \n\t\r");
            i++;
        }
        int pid = fork();
        int status;
        if (pid == 0)
        {
            pid_t proc_id = getpid();
            background[job_no].pi = proc_id;
            int j = 1;
            // for (i = 1; i <= back_c; i++)
            // {
            //     if (background[i].state == 1 && background[i].pi > 0)
            //     {
            //         printf("[%d]\t%s\t\t%s\t[%d]\n", j++, "Running", background[i].name, background[i].pi);
            //     }
            //     if (background[i].state == 0 && background[i].pi > 0)
            //     {
            //         printf("[%d]\t%s\t\t%s\t[%d]\n", j++, "Stopped", background[i].name, background[i].pi);
            //     }
            // }
            execvp(argv[0], argv);
            background[job_no].pi = proc_id;
        }
        else
        {
            printf("pid : %d\n", pid);
        }
        return;
    }
}
