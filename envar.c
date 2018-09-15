#include "header.h"
#include "envar.h"

void unsetenv_f(char *s)
{
    int cnt = 1, i, j;
    char *st[10];
    char *token = strtok(NULL, " \n\t\r");
    while (token != NULL)
    {
        st[cnt] = token;
        token = strtok(NULL, " \n\t\r");
        cnt++;
    }
    st[cnt] = '\0';
    if(cnt==1)
    {
        printf("ERROR , 0 ARGUMENTS NOT ALLOWED");
    }
    else
    {
        unsetenv(st[1]);
    }
    return;
}

void setenv_f(char *s)
{
    int cnt = 1, i, j;
    char *st[10];
    //printf("%s\n",s);
    char *token = strtok(NULL," ");
    //printf("token=%s\n",token);
    while (token != NULL)
    {
        st[cnt] = token;
        token = strtok(NULL, " ");
        cnt++;
    }
    st[cnt] = '\0';
    //printf("cnt=%d\n",cnt);
    if (cnt == 1)
    {
        printf("Arguments expected: {1,2} , given: 0\n");
    }
    else if (cnt > 3)
    {
        printf("Too many arguments\n");
    }
    else
    {
        if (cnt == 2)
        {
            setenv(st[1], " ", 2);
        }
        else
        {
            setenv(st[1], st[2], 2);
        }
    }
    return;
}
