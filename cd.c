#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <dirent.h>
#include "cd.h"
void cd_(char cwd[500],char dcwd[10000],char home_directory[500],char *extract,char prev_dir[500],int home_size,char relative_path[1000])
{
    memset(dcwd, '\0', sizeof(char) * 10000);
    // printf("yes\n");
    extract = strtok(NULL, " ");
    // printf("%s\n",extract);
    if (extract == NULL)
    {
        return;
    }
    else if (strcmp(extract, "-") == 0)
    {
        // printf("hello1\n");
        char temp[1024];
        // printf("%s\n",prev_dir);
        strcpy(temp, prev_dir);
        // printf("%s\n",temp);
        chdir(prev_dir);
        strcpy(prev_dir, temp);
        printf("%s\n", prev_dir);
        return;
    }
    char *hi = (char *)malloc(1024);
    getcwd(hi, 100);
    strcpy(prev_dir, hi);
    if (strcmp(extract, "..") == 0)
    {
        chdir(extract);
        if (getcwd(cwd, 100) == NULL)
        {
            perror("Error");
            exit(0);
        }
        // printf("%s\n", cwd);
    }
    else if (strcmp(extract, ".") == 0)
    {
        return;
    }

    else if (strcmp(extract, "~") == 0)
    {
        chdir(home_directory);
    }
    else
    {
        char curr[100];
        getcwd(curr, 100);
        strcpy(dcwd, curr);

        int p = strlen(dcwd);
        dcwd[p] = '/';
        dcwd[p + 1] = '\0';
        strcat(dcwd, extract);
        // printf("%s\n", dcwd);
        // printf("%d", chdir(dcwd));
        int ret = chdir(dcwd);
        if (ret == -1)
        {
            printf("Directory doesn't exist :\n");
            return;
        }
        else
        {
            int j = 0;
            int size = strlen(cwd);
            char dcwd2[10000];
            if (getcwd(dcwd2, 100) == NULL)
            {
                perror("Error");
                exit(0);
            }
            // printf("%s\n",dcwd2);
            if (strncmp(dcwd2, home_directory, home_size) == 0)
            {
                int bigsize = strlen(dcwd2);
                int j = 0;
                for (int i = home_size; i <= bigsize; ++i)
                {
                    relative_path[j] = dcwd2[i];
                    // printf("%c",relative_path[j]);
                    j++;
                }
                // printf("here: %s\n", relative_path);
                // printf("\033[;36m<%s@%s~%s>\033[0m\n", name, sysname, relative_path);
                return;
            }
        }
    }
}
