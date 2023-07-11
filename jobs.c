#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
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
#include <math.h>
#include "jobs.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "history.h"
#include "ls.h"
#include "discovery.h"
#include "foreground.h"
#include "background.h"
#include "variable.h"
#include "signals.h"
struct PINFO_ PINFO;
// PINFO.bgarray[1000];
// int bgarray_copy[1000];
// int compare(const void *arg1, const void *arg2)
// {
//     return (strcmp(*(char **)arg1, *(char **)arg2));
// }
void func(char *vrinda)
{
    char path[1000];
    strcpy(path, "proc/");
    // path[4] = "proc/";
    int temp;
    char temp1[100];
    int k = 0;
    while (vrinda[k] != NULL)
    {
        if (strcmp(vrinda[k], "r") == 0)
        {
            for (int i = 0; i < 1000; i++)
            {
                if (PINFO.bgarray[i] == 0)
                {
                    continue;
                }
                char this[100];
                sprintf(this, "%d", PINFO.bgarray[i]);
                strcat(path, this);
                strcat(path, "/stat");
                FILE *file = fopen(path, "r");
                if (file)
                {
                    fscanf(file, "%d %s %c", &temp, temp1, &PINFO.bg_status[i]);
                }
                if (PINFO.bg_status[i] == 'R')
                {
                    printf("[%d] \n", PINFO.bg_index);
                    printf("%s [%d]\n", PINFO.bg_names[i], PINFO.bgarray[i]);
                }
            }
        }
        else if (strcmp(vrinda[k], "s") == 0)
        {
            for (int i = 0; i < 1000; i++)
            {
                if (PINFO.bgarray[i] == 0)
                {
                    continue;
                }
                char this[100];
                sprintf(this, "%d", PINFO.bgarray[i]);
                strcat(path, this);
                strcat(path, "/stat");
                FILE *file = fopen(path, "r");
                if (file)
                {
                    fscanf(file, "%d %s %c", &temp, temp1, &PINFO.bg_status[i]);
                }
                if (PINFO.bg_status[i] == 'S')
                {
                    printf("[%d] \n", PINFO.bg_index);
                    printf("%s [%d]\n", PINFO.bg_names[i], PINFO.bgarray[i]);
                }
            }
        }
        else
        {
            for (int i = 0; i < 1000; i++)
            {
                if (PINFO.bgarray[i] == 0)
                {
                    continue;
                }
                char this[100];
                sprintf(this, "%d", PINFO.bgarray[i]);
                strcat(path, this);
                strcat(path, "/stat");
                FILE *file = fopen(path, "r");
                if (file)
                {
                    fscanf(file, "%d %s %c", &temp, temp1, &PINFO.bg_status[i]);
                }
                printf("[%d] \n", PINFO.bg_index);
                printf("%s [%d]\n", PINFO.bg_names[i], PINFO.bgarray[i]);
            }
        }
    }
}
void bgfunc(char *vrinda)
{
    char idd[10];
    strcpy(idd, &vrinda[3]);
    for (int i = 0; i < 1000; i++)
    {
        if (atoi(idd) == PINFO.bgarray[i])
        {
            kill(idd, SIGCONT);
        }
    }
}
void fgfunc(char *vrinda)
{
    char iddd[10];
    strcpy(iddd, &vrinda[3]);
    for (int i = 0; i < 1000; i++)
    {
        int status;
        if (atoi(iddd) == PINFO.bgarray[i])
        {
            kill(iddd, SIGCONT);
            waitpid(iddd, &status, WUNTRACED);
        }
    }
}
