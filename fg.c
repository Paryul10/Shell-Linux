#include "header.h"
#include "variables.h"
#include "fg.h"

void fg(char st[][100])
{
    int job_no = atoi(st[1]);
    if (job_no > back_c)
    {
        printf("NO SUCH FG PROCESS EXISTS\n");
        return;
    }
    else if (background[job_no].state == 1)
    {
        int s;
        printf("%s\n", background[job_no].name);
        waitpid(background[job_no].pi, &s, 0);
        background[job_no].state=0;
    }
    else if (background[job_no].state == 0)
    {
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
            setpgid(proc_id, background[job_no].pi);
            execvp(argv[0], argv);
        }
        else
        {
            while (wait(&status) != pid)
                ;
        }
        return;
    }
}
