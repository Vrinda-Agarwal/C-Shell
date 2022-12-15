#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include "ls.h"
#include "cd.h"
#include "discovery.h"
#include <dirent.h>

void discoveryy(char curr_dir[500])
{
    // puts("hi");
    DIR *d;
    struct dirent *di;
    struct stat tstat;
    d = opendir(curr_dir);
    if (d == NULL)
        return;
    //puts("hi");
    // char curr_dir[500];
    // if (getcwd(curr_dir, 100) == NULL)
    // {
    //     perror("Error1");
    //     exit(0);
    // }
    di = readdir(d);
    while (di != NULL)
    {
        // puts("hi");
        if (di->d_name[0] == '.')
        {
            di = readdir(d);
            continue;
        }
        char temp_dir[500];
        strcpy(temp_dir, curr_dir);
        strcat(temp_dir, "/");
        strcat(temp_dir, di->d_name);
        printf("%s\n", temp_dir);
        discoveryy(temp_dir);
        // printf("%s\n", di->d_name);
        di = readdir(d);

    }
}
void discoveryf(char curr_dir[500])
{
    DIR *d;
    struct dirent *di;
    struct stat tstat;
    d = opendir(curr_dir);
    if (!d)
        return;
    // struct dirent *di;
    // struct stat tstat;
    // char curr_dir[500];
    // if (getcwd(curr_dir, 100) == NULL)
    // {
    //     perror("Error1");
    //     exit(0);
    // }
    while ((di = readdir(d)) != NULL)
    {
        if (di->d_name[0] == '.')
        {
            continue;
        }

        char temp_dir[500];
        strcpy(temp_dir, curr_dir);
        strcat(temp_dir, "/");
        strcat(temp_dir, di->d_name);
        stat(temp_dir, &tstat);
        if (S_ISREG(tstat.st_mode) != 0)
        {
            printf("%s\n", temp_dir);
        }
        discoveryf(temp_dir);
        // printf("%s\n", di->d_name);
    }
}
void discoveryd(char curr_dir[500])
{
    DIR *d;
    struct dirent *di;
    struct stat tstat;
    d = opendir(curr_dir);
    if (!d)
        return;
    // struct dirent *di;
    // struct stat tstat;
    // char curr_dir[500];
    // if (getcwd(curr_dir, 100) == NULL)
    // {
    //     perror("Error1");
    //     exit(0);
    // }
    while ((di = readdir(d)) != NULL)
    {
        char temp_dir[500];
        if (di->d_name[0] == '.')
        {
            continue;
        }
        strcpy(temp_dir, curr_dir);
        strcat(temp_dir, "/");
        strcat(temp_dir, di->d_name);
        stat(temp_dir, &tstat);
        if (S_ISDIR(tstat.st_mode))
        {

            printf("%s\n", temp_dir);
        }

        discoveryd(temp_dir);
        // printf("%s\n", di->d_name);
    }
}
void discovery(char *input, char *extract, char home_directory[500])
{
    // printf("%s\n", extract);
    int flag_dot = 0, flag_tilda = 0, flag_dd = 0, flag_d = 0, flag_f = 0;
    char flag_dir[100] = "\0";
    extract = strtok(NULL, " ");
    while (extract != NULL)
    {
        // printf("%s\n",ext);
        if (strcmp(extract, "-d") == 0)
        {
            flag_d = 1;
        }
        else if (strcmp(extract, "-f") == 0)
        {
            flag_f = 1;
        }
        else if (strcmp(extract, ".") == 0)
        {
            flag_dot = 1;
        }
        else if (strcmp(extract, "..") == 0)
        {
            flag_dd = 1;
        }
        else if (strcmp(extract, "~") == 0 || strcmp(extract, "~/") == 0)
        {
            flag_tilda = 1;
        }
        else
        {
            strcpy(flag_dir, extract);
            // printf("%s\n",flag_dir);
        }
        extract = strtok(NULL, " ");
    }
    char currr_dir[500];
    if (getcwd(currr_dir, 100) == NULL)
    {
        perror("Error1");
        exit(0);
    }
    if (strcmp(flag_dir, "\0") == 0)
    {

        if (flag_d == 0 && flag_f == 1 && flag_dot == 1)
        {
            //printf("hi7\n");
            discoveryf(".");
        }
        else if (flag_d == 1 && flag_f == 0 && flag_dot == 1)
        {
            //printf("hi8\n");
            discoveryd(".");
        }
        else if (flag_d == 1 && flag_f == 1 && flag_dot == 1)
        {
            //printf("hi9\n");
            discoveryy(".");
        }
        else if (flag_d == 0 && flag_f == 0 && flag_dot == 1)
        {
            //printf("hi9\n");
            discoveryy(".");
        }
        else if (flag_d == 1 && flag_f == 1 && flag_tilda == 1)
        {
            //printf("hi9\n");
            discoveryy(home_directory);
        }
        else if (flag_d == 1 && flag_f == 0 && flag_tilda == 1)
        {
            //printf("hi8\n");
            discoveryd(home_directory);
        }
        else if (flag_d == 0 && flag_f == 1 && flag_tilda == 1)
        {
            //printf("hi8\n");
            discoveryf(home_directory);
        }
        else if (flag_d == 0 && flag_f == 0 && flag_tilda == 1)
        {
            //printf("hi8\n");
            discoveryy(home_directory);
        }
        else if (flag_d == 0 && flag_f == 1 && flag_dd == 1)
        {
            //printf("hi7\n");
            discoveryf("..");
        }
        else if (flag_d == 1 && flag_f == 0 && flag_dd == 1)
        {
            //printf("hi8\n");
            discoveryd("..");
        }
        else if (flag_d == 1 && flag_f == 1 && flag_dd == 1)
        {
            //printf("hi9\n");
            discoveryy("..");
        }
        else if (flag_d == 0 && flag_f == 0 && flag_dd == 1)
        {
            //printf("hi9\n");
            discoveryy("..");
        }
        else if (flag_d == 1 && flag_f == 1)
        {
            //printf("hi1\n");
            discoveryy(".");
        }
        else if (flag_d == 1 && flag_f == 0)
        {
            //printf("hi2\n");
            discoveryd(".");
        }
        else if (flag_d == 0 && flag_f == 1)
        {
            //printf("hi3\n");
            discoveryf(".");
        }
        else if (flag_d == 0 && flag_f == 0)
        {
            //printf("hi3\n");
            discoveryy(".");
        }
    }
    else
    {
        if (flag_d == 1 && flag_f == 0)
        {
            //printf("hi4\n");
            char target_dir[500];
            strcpy(target_dir, currr_dir);
            strcat(target_dir, "/");
            strcat(target_dir, flag_dir);
            // printf("%s\n",target_dir);
            discoveryd(flag_dir);
        }
        else if (flag_d == 0 && flag_f == 1)
        {
            //printf("hi5\n");
            char target_dir[500];
            strcpy(target_dir, currr_dir);
            strcat(target_dir, "/");
            strcat(target_dir, flag_dir);
            //printf("%s\n", target_dir);
            discoveryf(flag_dir);
        }
        else if (flag_d == 1 && flag_f == 1)
        {
            //printf("hey\n");
            char target_dir[500];
            strcpy(target_dir, currr_dir);
            strcat(target_dir, "/");
            strcat(target_dir, flag_dir);
            //printf("%s\n", target_dir);
            discoveryy(flag_dir);
        }
        else if (flag_d == 0 && flag_f == 0)
        {
            //printf("hey\n");
            char target_dir[500];
            strcpy(target_dir, currr_dir);
            strcat(target_dir, "/");
            strcat(target_dir, flag_dir);
            //printf("%s\n", target_dir);
            discoveryy(flag_dir);
        }
    }
}