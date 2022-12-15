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
#include "foreground.h"
void foreground(char *input1)
{
    int i;
    char *arg[1000];
    for (i = 0; i < 1000; i++)
    {
        arg[i] = (char *)malloc(sizeof(char) * 1000);
    }
    int count = 0;
    char *token = strtok(input1, " ");
    while (token != NULL)
    {
        //printf("%s\n",token);
        arg[count] = token;
        count++;
        token = strtok(NULL, " ");
    }
    arg[count]=NULL;
    pid_t child_pid;
    int child_status;
    char *extract1 = (char *)malloc(sizeof(char) * 1000);
    // int a_count = 0,q=0;
    //printf("%s\n", input1);
    // strcpy(extract1,input1);
    //    for(i=0;i<strlen(input1);i++)
    //    {
    //         if(input1[i] == '&')
    //         {
    //             a_count++;
    //             q = i;
    //         }
    //    }
    // while (extract1 != NULL)
    // {
    //     printf("hi\n");
    //     if (strcmp(extract1, "&") == 0)
    //     {
    //         a_count++;
    //     }
    //     printf("%s\n", extract1);
    //     extract1 = strtok(NULL, " ");
    // }
    child_pid = fork();
    if (child_pid == 0)
    {
        execvp(arg[0], arg);
        printf("Unknown command\n");
        exit(0);
    }
    else
    {
        //pid_t tpid;
        // while (tpid != child_pid)
        // {
        //     pid_t tpid = wait(&child_status);
        // }
        waitpid(child_pid,&child_status,WCONTINUED|WUNTRACED);
    }
}