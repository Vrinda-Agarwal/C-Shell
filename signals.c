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
#include<time.h>
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
#include "variable.h"
#include "jobs.h"
//PINFO.bgarray[1000];
//int bgarray_copy[1000];
extern struct PINFO_ PINFO;
// int compared(const void *arg1, const void *arg2)
// {
//     return (strcmp(*(char **)arg1, *(char **)arg2));
// }
void sig_func(char *input){
    for(int i=0;i<1000;i++){
        if(PINFO.bgarray[i]==0){
            continue;
        }
        else{
            int var;
            if( waitpid(PINFO.bgarray[i], &var, WNOHANG) != 0 )
            {
                if(WIFEXITED(var) != 0)
                {
                    printf("process with id %d has exited in an abnormal way\n",PINFO.bgarray[i]);
                }
                else if (WIFEXITED(var) == 0)
                {
                    printf("process with id %d has exited in a normal way\n",PINFO.bgarray[i]);
                }
            }
            PINFO.bg_names[i] = (char *)malloc(sizeof(char)*100);
            strcpy(PINFO.bg_names[i],input);
            //PINFO.bg_names=input;
            PINFO.bgarray[i]=0;
        }
    }
    // int i;
    // for(i=0;i<1000;i++){
    //     bgarray_copy[i]=bgarray[i];
    // }
    //qsort(bgarray, i, sizeof(char *), compare);
    return;
}
// ctrl c ke signal ke liye func call banana hai
void sig_int()
{
    printf("Exiting the terminal \n");
    exit(0);
}
