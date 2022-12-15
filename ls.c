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
int compare(const void *arg1, const void *arg2)
{
    return (strcmp(*(char **)arg1, *(char **)arg2));
}
void ls_(char *input, char *extract)
{
    char *directory = NULL;
    char s1[] = " ";
    // char *extract1=(char*)malloc(100*sizeof(char));
    char *extract1 = strtok(NULL, s1);
    //printf("%s\n",extract1);
    // extract1 = strtok(NULL, s1);
    // printf("%s\n",extract1);
    // if(extract1 == NULL) {
    //     printf("%s\n", extract1);
    // }
    // printf("%s\n",extract);
    // printf("%s\n",extract1);
    char dir[500];
    // strcpy(dir, ".");
    struct dirent *di;
    if (getcwd(dir, 100) == NULL)
    {
        perror("Error");
        exit(0);
    }
    if (extract1 == NULL || strcmp(extract1, ".") == 0)
    {
        // printf("hello\n");
        DIR *d = opendir(".");

        while ((di = readdir(d)) != NULL)
        {
            if (di->d_name[0] == '.')
            {
                continue;
            }
            printf("%s\n", di->d_name);
        }
    }
    else if (strcmp(extract1, "..") == 0)
    {
        // printf("hi\n");
        DIR *d = opendir("..");
        // chdir(extract1);
        while ((di = readdir(d)) != NULL)
        {
            if (di->d_name[0] == '.')
            {
                continue;
            }
            printf("%s\n", di->d_name);
        }
        closedir(d);
        // rewinddir(d);
    }
    else
    {
        char *p;
        p = strdup(extract1);
        //printf("%s\nhi\n",p);
        int flag, flag__, flag_a, flag_l, flag_la = 0;
        // printf("%s\n", p);
        while (p != NULL)
        {
            // printf("hey\t%s\n",p);
            // printf(" %s\n", p);
            if (strcmp(p, "-a") == 0)
            {
                flag_a = 1;
            }
            else if (strcmp(p, "-l") == 0)
            {
                flag_l = 1;
            }
            else if (strcmp(p, "-al") == 0 || strcmp(p, "-la") == 0)
            {
                flag_la = 1;
            }
            else
            {
                //printf("HII\n");
                directory = (char *)malloc(sizeof(char) * 4096);
                strcpy(directory, p);
                // printf("directory is: %s\n", directory);
            }
            p = strtok(NULL, " ");
            // printf("p is:%s\n",p);
        }
        if (directory == NULL)
        {
            directory = (char *)malloc(sizeof(char) * 100);
            strcpy(directory, ".");
        }
        // printf("%s\n", directory);
        //  printf("%d\n%d\n%d\n%d\n%d\n", flag_a, flag_l, flag_la,flag,flag__);
        // printf("90\n");
        if (flag_la == 1 || (flag_a == 1 && flag_l == 1))
        {
            // printf("92\n");
            DIR *d;
            struct stat tstat;
            struct passwd *t;
            struct group *g;
            char buf[512];
            if (getcwd(dir, 100) == NULL)
            {
                perror("Error1");
                exit(0);
            }
            printf("%s\n",dir);
            d = opendir(directory);
            chdir(directory);
            // if (getcwd(dir, 100) == NULL)
            // {
            //     perror("Error1");
            //     exit(0);
            // }
            char *array[1000];
            int i = 0;
            while ((di = readdir(d)) != NULL)
            {
                array[i] = (malloc(100 * sizeof(char)));
                strcpy(array[i], di->d_name);
                // array[i]=*strdup(di->d_name);
                i += 1;
            }
            // printf("%d\n",i);
            qsort(array, i, sizeof(char *), compare);
            // printf("hi\n");
            for (int j = 0; j < i; ++j)
            {
                //printf("hi1\n");
                strcpy(buf, array[j]);
                //printf("hi\n");
                //printf("%s\n",buf);
                if (stat(buf, &tstat) < 0)
                {
                    //printf("hi222\n");
                    // perror("Error");
                    exit(1);
                }
                //printf("hi\n");
                if (tstat.st_mode & S_IFBLK)
                {
                    printf("b ");
                }
                else if (tstat.st_mode & S_IFCHR)
                {
                    printf("c ");
                }
                else if (tstat.st_mode & S_IFDIR)
                {
                    printf("d ");
                }
                else if (tstat.st_mode & S_IFIFO)
                {
                    printf("p ");
                }
                else if (tstat.st_mode & S_IFLNK)
                {
                    printf("l ");
                }
                else if (tstat.st_mode & S_IFSOCK)
                {
                    printf("s ");
                }
                else
                {
                    printf("- ");
                }
                // permissions
                printf((tstat.st_mode & S_IRUSR) ? " r" : " -");
                printf((tstat.st_mode & S_IWUSR) ? "w" : "-");
                printf((tstat.st_mode & S_IXUSR) ? "x" : "-");
                printf((tstat.st_mode & S_IRGRP) ? "r" : "-");
                printf((tstat.st_mode & S_IWGRP) ? "w" : "-");
                printf((tstat.st_mode & S_IXGRP) ? "x" : "-");
                printf((tstat.st_mode & S_IROTH) ? "r" : "-");
                printf((tstat.st_mode & S_IWOTH) ? "w" : "-");
                printf((tstat.st_mode & S_IXOTH) ? "x" : "-");
                // number of hard links
                printf(" %ld ", tstat.st_nlink);
                // owner
                t = getpwuid(tstat.st_uid);
                printf("\t%s", t->pw_name);
                // group
                g = getgrgid(tstat.st_gid);
                printf("\t%s ", g->gr_name);
                // size in bytes,filename
                printf("\t%ld\t", tstat.st_size);
                struct tm *time = localtime(&(tstat.st_mtime));
                // strftime(buff,20,"%b %d %H:%M", time);
                char buffer1[40];
                strftime(buffer1, 40, "%b %d %H:%M", time);
                printf("\t%s\t", buffer1);
                printf("%s\n", array[j]);
            }
            chdir(dir);
        }
        else if (flag_a == 1)
        {
            // printf("183\n");
            char *extract1 = directory;
            char *p2 = NULL;
            if (extract1 != NULL)
                p2 = strdup(extract1);
            // while (p2!=NULL)
            // {
            //     printf("in\n");
            //     printf(" %s\n", p2);
            //     if (strcmp(p2, "..") == 0)
            //     {
            //         flag = 1;
            //     }
            //     p2 = strtok(NULL, " ");
            // }
            // printf("198\n");
            DIR *d = opendir(directory);
            if (getcwd(dir, 100) == NULL)
            {
                perror("Error");
                exit(0);
            }
            while ((di = readdir(d)) != NULL)
            {
                printf("%s\n", di->d_name);
            }

            // printf("212\n");
            // DIR *d = opendir(".");
            // if (getcwd(dir, 100) == NULL)
            // {
            //     perror("Error");
            //     exit(0);
            // }
            // while ((di = readdir(d)) != NULL)
            // {
            //     printf("%s\n", di->d_name);
            // }
            // chdir(dir);
        }
        else if (flag_l == 1)
        {
            //printf("aSa\n");
            char *extract2 = directory;
            //printf("%s\n", extract2);
            char *p3 = NULL;
            if (extract2 != NULL)
                p3 = strdup(extract2);
            // printf("p3 is: %s\n",p3);
            /*while (p3 != NULL)
            {
                // printf(" %s\n", p);
                if (strcmp(p3, "..") == 0)
                {
                    flag__= 1;
                }
                //p3 = strtok(NULL, " ");
            }*/
            DIR *d;
            struct stat *tstat = (struct stat *)malloc(sizeof(struct stat));
            struct passwd *t;
            struct group *g;
            char buf[512];
            /*if(flag__==1){
                d=opendir("..");
            }
            else{
                //printf("hi\n");
                d = opendir(".");
            }*/
            //printf("%s\n", directory);
            d = opendir(directory);
            if (getcwd(dir, 100) == NULL)
            {
                perror("Error1");
                exit(0);
            }
            char *array[1000];
            int i = 0;
            while ((di = readdir(d)) != NULL)
            {
                if (di->d_name[0] == '.')
                {
                    continue;
                }
                array[i] = (malloc(100 * sizeof(char)));
                strcpy(array[i], di->d_name);
                // array[i]=*strdup(di->d_name);
                i += 1;
            }
            // printf("%d\n",i);
            qsort(array, i, sizeof(char *), compare);
            // printf("hi\n");
            chdir(directory);
            for (int j = 0; j < i; ++j)
            {
                strcpy(buf, array[j]);
                // printf("buf is:%s\n",buf);
                if (stat(buf, tstat) < 0)
                {
                    perror("Error");
                    exit(0);
                }
                // printf("done");
                //  printf("hi\n");
                if (tstat->st_mode & S_IFBLK)
                {
                    printf("b ");
                }
                else if (tstat->st_mode & S_IFCHR)
                {
                    printf("c ");
                }
                else if (tstat->st_mode & S_IFDIR)
                {
                    printf("d ");
                }
                else if (tstat->st_mode & S_IFIFO)
                {
                    printf("p ");
                }
                else if (tstat->st_mode & S_IFLNK)
                {
                    printf("l ");
                }
                else if (tstat->st_mode & S_IFSOCK)
                {
                    printf("s ");
                }
                else
                {
                    printf("- ");
                }
                // permissions
                printf((tstat->st_mode & S_IRUSR) ? " r" : " -");
                printf((tstat->st_mode & S_IWUSR) ? "w" : "-");
                printf((tstat->st_mode & S_IXUSR) ? "x" : "-");
                printf((tstat->st_mode & S_IRGRP) ? "r" : "-");
                printf((tstat->st_mode & S_IWGRP) ? "w" : "-");
                printf((tstat->st_mode & S_IXGRP) ? "x" : "-");
                printf((tstat->st_mode & S_IROTH) ? "r" : "-");
                printf((tstat->st_mode & S_IWOTH) ? "w" : "-");
                printf((tstat->st_mode & S_IXOTH) ? "x" : "-");
                // number of hard links
                printf(" %d ", tstat->st_nlink);
                // owner
                t = getpwuid(tstat->st_uid);
                printf("\t%s\t", t->pw_name);
                // group
                g = getgrgid(tstat->st_gid);
                printf("%s\t", g->gr_name);
                // size in bytes,filename
                printf("%lld\t", tstat->st_size);
                struct tm *time = localtime(&(tstat->st_mtime));
                // strftime(buff,20,"%b %d %H:%M", time);
                char buffer1[40];
                strftime(buffer1, 40, "%b %d %H:%M", time);
                printf("%s\t", buffer1);
                printf("%s\n", array[j]);

                // printf("%s\n", array[j]);
            }
            printf("%s\n",dir);
            chdir(dir);
            //closedir(d);
        }
    }
}
