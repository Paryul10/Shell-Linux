#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "pipe.h"

int inp_red(char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if ((s[i] == '<'))
            return 1;
        i++;
    }
    return 0;
}

int out_red(char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if ((s[i] == '>'))
            return 1;
        i++;
    }
    return 0;
}

void execute_pipe(char ***command, int cnt)
{
    int c = 0;
    int p[2]; //p[0] = read end of the pipe   , p[1] = write end of the pipe
    pid_t pid;
    int fd_in = 0;

    while (*command != NULL) // while not all commands are executed from the commmand set
    {
        int k = pipe(p);
        if (k < 0)
        {
            printf("PIPE NOT OPENED SUCCESFULLY\n");
            exit(1);
        }
        int ir = 0, i = 0, l = 0, or = 0;
        if ((pid = fork()) == -1)
        {
            printf("Fork Failed\n");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            printf("1 entry\n");
            dup2(fd_in, 0);
            if (c != (cnt-1)) // i.e there are more commands after this command seperated thru a pipe
            {
                //printf("2 entry \n");
                dup2(p[1], 1); // the write end of the pipe is copied in fd = 1
            }

            close(p[0]); //close the unused end of the pipe

            ir = inp_red((*command)[0]);
            or = out_red((*command)[0]);

            if (ir == 1)
            {
                int l = 0, m = 0, n = 0;

                char *ip[2];
                ip[0] = strtok((*command)[0], "<");
                ip[1] = strtok(NULL, "<");

                char *tmp;
                char st[100][100];
                tmp = strtok(ip[0], " \n\t\r");
                while (tmp != NULL)
                {
                    strcpy(st[l], tmp);
                    tmp = strtok(NULL, " \n\t\r");
                    l++;
                }

                char *cmd[l + 1];
                while (m < l)
                {
                    cmd[m] = st[m];
                    m++;
                }
                cmd[m] = NULL;

                char *tmp2 = strtok(ip[1], " \n\t\r");
                if (tmp2 != NULL)
                {
                    int inp_file = open(tmp2, O_RDONLY);
                    if (inp_file > 0)
                    {
                        dup2(inp_file, 0); // read from inp_file instead of stdin
                    }
                    else
                    {
                        printf("File does not exist\n");
                    }
                }
                execvp(cmd[0], cmd);
            }
            if (or == 1)
            {
               // printf("yeas\n");
                int l = 0, m = 0, n = 0;

                char *op[2];
                op[0] = strtok((*command)[0], ">");
                op[1] = strtok(NULL, ">");

                char *tmp;
                char st[100][100];
                tmp = strtok(op[0], " \n\t\r");
                while (tmp != NULL)
                {
                    strcpy(st[l], tmp);
                    tmp = strtok(NULL, " \n\t\r");
                    l++;
                }

                char *cmd[l + 1];
                while (m < l)
                {
                    cmd[m] = st[m];
                    m++;
                }
                cmd[m] = NULL;

                char *tmp2 = strtok(op[1], " \n\t\r");
                if (tmp2 != NULL)
                {
                    int out_file = open(tmp2, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
                    dup2(out_file, 1); //write into out_file instead of stdout
                    execvp(cmd[0], cmd);
                }
            }
            else
            {
                execvp((*command)[0], *command);
            }
            exit(EXIT_FAILURE);
        }
        else
        {
            //printf("YESS\n");
            wait(NULL);
            close(p[1]);
            fd_in = p[0];
            command++;
            c++;
        }
    }
}

void parsepipe(char *s)
{
   //printf("pipie entry\n");
    int i = 0, j = 0;
    int cnt = 0;
    char *rest1;
    char *token = strtok_r(s, "|", &rest1);                    //stores the rest of the string in rest1 , token contains all of the string
    char ***command = (char ***)malloc(sizeof(char **) * 100); //stores every command seperated by a pipe and then breaks that command into its constituent commands arg arraay waala

    while (token != NULL)
    {
        j = 0;
        command[i] = (char **)malloc(sizeof(char *) * 100);
        char *rest2;
        char *token2 = strtok_r(token, " \n\t\r", &rest2);
        while (token2 != NULL)
        {
            command[i][j] = (char *)malloc(sizeof(char) * 100); // this stores on command ka part  like if echo "anything"  so it stores echo
            strcpy(command[i][j], token2);
            token2 = strtok_r(NULL, " \n\t\r", &rest2);
            j++;
        }
        command[i][j] = NULL; // for null terminating string
        token = strtok_r(NULL, "|", &rest1);
        cnt++;
        i++; // next command set after a pipe
    }
    command[i] = NULL;
    execute_pipe(command, cnt);
}