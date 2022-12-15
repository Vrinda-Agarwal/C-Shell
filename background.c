#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "history.h"
#include "ls.h"
#include "discovery.h"
#include "foreground.h"
#include "background.h"
extern int bg_index;
extern int bgarray[1000];
char *ss = " \t\n";
void background(char *vrinda, int no_of_com)
{
    int i;
    char *arg[1000];
    for (i = 0; i < 1000; i++)
    {
        arg[i] = (char *)malloc(sizeof(char) * 1000);
    }
    int count = 0;
    char *token = strtok(vrinda, ss);
    // printf("%s\n",token);
    while (token != NULL)
    {
        // printf("%s\n",token);
        arg[count] = token;
        count++;
        token = strtok(NULL, ss);
    }
    arg[count] = NULL;
    pid_t child_pid;
    int child_status;
    // char *extract1 = (char *)malloc(sizeof(char*));
    child_pid = fork();
    if (child_pid == 0)
    {
        execvp(arg[0], arg);
        printf("Unknown command\n");
        exit(0);
    }
    else
    {
        // pid_t tpid;
        //  while (tpid != child_pid)
        //  {
        //      pid_t tpid = wait(&child_status);
        //  }
        bgarray[bg_index] = child_pid;
        //strcpy(bg_names[bg_index], vrinda);
        //bg_names[bg_index] = vrinda; copy kardena
        // vrinda copy kar
        bg_index++;
        printf("[%d] %d\n", bg_index + 1, child_pid);
    }
}