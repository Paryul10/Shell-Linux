#include"header.h"
extern char OLDPWD[2000] , HOME[2000];
extern char *internal_commands[];
extern int file_in;
extern int file_out;
extern int background_jobs;
extern int child_pid;
typedef struct jobs{
    char status[10], name[101];
    pid_t pid;
    int flag;  
}jobs;
typedef struct back
{
	char name[100],status[100];
	int pi;
	int state;
}back;
extern jobs job[1010];
extern int mode;
extern int back_c;
extern int curid;
extern back background[100];
