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
#include "jobs.h"
#include "background.h"
int flag;
int bgarray[1000];
int bg_index;
int file_desc;
char *s = " \t\n";
typedef struct PINFO_ PINFO;
int main()
{
    char *bg_names[1000];
    for (int i = 0; i < 1000; i++)
    {
        bg_names[i] = (char *)malloc(sizeof(char) * 1000);
    }
    bg_index = 0;
    FILE *fd;
    char *buffer[1000];
    // char *hist[1000];
    int actual_in = dup(STDIN_FILENO);
    int actual_out = dup(STDOUT_FILENO);
    int z = 0;
    fd = fopen("history.txt", "r");
    if (fd == NULL)
    {
        perror("Error: Can't open file\n");
    }
    for (int i = 0; i < 1000; i++)
    {
        buffer[i] = (char *)malloc(sizeof(char) * 100);
    }
    while (1)
    {
        if (fgets(buffer[z], 1000, fd) == NULL)
            break;

        else if (buffer[z][strlen(buffer[z] - 1)] == '\n')
            buffer[z][strlen(buffer[z] - 1)] = '\0';

        z++;
    }
    buffer[z][strlen(buffer[z]) - 1] = '\0';
    fclose(fd);
    // for (int i = 0; i < z; i++)
    // {
    //     printf("%s", buffer[i]);
    // }
    char prev_dir[500];
    char *arr[1000];
    char home_directory[500];
    if (getcwd(home_directory, sizeof(home_directory)) == NULL)
    {
        perror("Error");
        return 0;
    }
    int home_size = strlen(home_directory);
    strcpy(prev_dir, home_directory);
    // printf("%s",home_directory);
    char prev[1000] = "\0";
    int a = dup(1);
    while (1)
    {
        long long int i = 0;
        char cwd[500];
        char dcwd[10000];
        char relative_path[1000];
        char *name = getlogin();
        int size = strlen(cwd);
        if (getcwd(cwd, 100) == NULL)
        {
            perror("Error");
            return 0;
        }
        char sysname[100];
        gethostname(sysname, 100);

        dup2(a, 1);
        if (strcmp(cwd, home_directory) == 0)
        {
            // dup2(1,file_desc)
            printf("\033[;36m<%s@%s~>\033[0m", name, sysname);
            // strcpy(prev_dir,home_directory);
        }
        else if (strcmp(cwd, home_directory) > 0)
        {
            int bigsize = strlen(cwd);
            int j = 0;
            for (int i = home_size; i <= bigsize; ++i)
            {
                relative_path[j] = cwd[i];
                // printf("%c",relative_path[j]);
                j++;
            }
            printf("\033[;36m<%s@%s~%s>\033[0m", name, sysname, relative_path);

            // printf("%s\n",prev_dir);
        }
        else
        {
            printf("\033[;36m<%s@%s~%s>\033[0m", name, sysname, cwd);
        }
        // printf("hello pro2\n");
        char *input;
        size_t inputsize = 5000;
        getline(&input, &inputsize, stdin);
        int l = strlen(input);
        input[l - 1] = '\0';
        strcpy(buffer[z++], input);
        // printf("hello pro3\n");
        char *input1 = (char *)malloc(sizeof(char) * 1024);
        strcpy(input1, input);
        int cmd_count = 0;
        char *extt = (char *)malloc(sizeof(char) * 1024);
        char *arraycmd[50];
        for (int i = 0; i < 50; i++)
        {
            arraycmd[i] = (char *)malloc(sizeof(char) * 1024);
        }
        arraycmd[cmd_count] = strtok(input1, ";");
        // printf("hello pro4\n");
        while (arraycmd[cmd_count] != NULL)
        {
            cmd_count++;
            arraycmd[cmd_count] = strtok(NULL, ";");
        }
        // printf("hello pro5\n");
        //  for(i=0;i<cmd_count;i++)
        //  {
        //      printf("%s\n",arraycmd[i]);
        //  }
        // printf("hello pro6\n");
        if (cmd_count == 0)
        {
            continue;
        }
        // printf("hello pro7\n");
        //  printf("%s\n",input1);
        // printf("%s\n",input);
        //   arr[i] = strdup(input);
        int sz;
        int k = 0;
        int hist_count = 0;
        // char *aray[1000]=(char *)malloc(sizeof(char)*100);
        //  if (strcmp(prev, input) != 0)
        //  {
        //      aray[k] = input;
        //      int fd1 = open("history.txt", O_RDWR, 0);
        //      // read(fd1, );
        //      sz = write(fd, input, strlen(input));
        //      sz = write(fd, "\n", strlen("\n"));
        //  }
        strcpy(prev, input);
        // printf("%s\n",prev);
        // printf("hello pro8\n");
        // i += 1;
        // char *s = " \t\n";
        char *extract;
        char *vrinda = (char *)malloc(sizeof(char) * 1024);
        // char *pp = (char *)malloc(sizeof(char) * 1024);
        for (int i = 0; i < cmd_count; i++)
        {
            flag = 0;
            if (arraycmd[i][strlen(arraycmd[i]) - 1] == '&')
            {
                flag = 1;
            }
            // printf("hello pro%d\n",i);
            // strcpy(vrinda, arraycmd[i]);
            // strcpy(pp, vrinda);
            char *arraygg[50];
            int gg_count = 0;
            for (int i = 0; i < 50; i++)
                arraygg[i] = (char *)malloc(sizeof(char) * 1024);

            arraygg[gg_count] = strtok(arraycmd[i], "&");
            while (arraygg[gg_count] != NULL)
            {
                gg_count++;
                arraygg[gg_count] = strtok(NULL, "&");
            }
            int k = gg_count - 1;
            if (flag == 1)
                k = gg_count;
            // printf("HIII\n");
            for (int i = gg_count - 1; i >= 0; i--)
            {
                // l++;
                // strcpy(buffer[l], arraygg[i]);
                // printf("HII\n");
                strcpy(vrinda, arraygg[i]);
                // printf("%d\n",flag);
                if (flag == 1)
                {
                    background(vrinda, k);
                }
                else
                {
                    extract = strtok(arraygg[i], s);
                    // printf("HIII\n");
                    //  printf("%s\n",extract);
                    char *copy[500];
                    copy[0] = (char *)malloc(sizeof(char) * 1024);
                    strcpy(copy[0], input);
                    // printf("22\n");
                    int j = 0, flagg = 0, encounter_index = 0;
                    while (copy[0][j] != '\0')
                    {
                        // if (strcmp(&copy[0][j], ">") == 0)
                        if (copy[0][j] == '>')
                        {
                            encounter_index = j;
                            flagg++;
                        }
                        j++;
                    }
                    // printf("22\n");
                    // printf("%d\n",flagg);
                    if (flagg > 0)
                    {
                        if (flagg == 1)
                        {
                            // printf("%s\n",extract);
                            char file_name[500];
                            int l = 0;
                            // int chmod(const char *path, mode_t mode);
                            strcpy(file_name, &copy[0][encounter_index + 1]);
                            int p = 0;
                            int file_desc = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                            // chmod(file_name, 0644);
                            if (file_desc < 0)
                                printf("Error opening the file\n");

                            // a = dup(1);
                            dup2(file_desc, 1);
                            // printf("Hi\n");
                            copy[0] = strtok(input, " \t\n");
                            int i = 0;
                            // while (copy[i] != NULL)
                            // {
                            //     printf("%s ", copy[i]);
                            //     i++;
                            //     copy[i] = strtok(NULL, " \t\n");
                            // }
                            if (extract == NULL)
                            {
                                continue;
                            }
                            if (getcwd(cwd, sizeof(cwd)) == NULL)
                            {
                                perror("Error");
                                return 0;
                            }
                            if (strcmp(extract, "cd") == 0)
                            {
                                cd_(cwd, dcwd, home_directory, extract, prev_dir, home_size, relative_path);
                            }
                            else if (strcmp(extract, "pwd") == 0)
                            {
                                pwd(cwd);
                            }
                            else if (strcmp(extract, "echo") == 0)
                            {
                                // printf("pohoch gye\n");
                                //  actual_out
                                echo_p(extract, vrinda);
                            }
                            else if (strcmp(extract, "q") == 0)
                            {
                                FILE *fd2 = fopen("history.txt", "w");
                                if (fd2 == NULL)
                                {
                                    perror("Error: Can't open file\n");
                                }
                                if (z > 20)
                                {
                                    for (int i = z - 20; i < z; i++)
                                    {
                                        fprintf(fd2, "%s\n", buffer[i]);
                                    }
                                }
                                else
                                {
                                    for (int i = 0; i < z; ++i)
                                    {
                                        fprintf(fd2, "%s\n", buffer[i]);
                                    }
                                }
                                fclose(fd2);
                                return 0;
                            }
                            else if (strcmp(extract, "ls") == 0)
                            {
                                ls_(vrinda, extract);
                            }
                            else if (strcmp(extract, "bg") == 0)
                            {
                                bgfunc(vrinda);
                            }
                            else if (strcmp(extract, "history") == 0)
                            {
                                // history(extract, vrinda);
                                if (z > 10)
                                {
                                    for (int i = z - 10; i < z; i++)
                                    {
                                        printf("%s\n", buffer[i]);
                                    }
                                }
                                else
                                {
                                    for (int i = 0; i < z; ++i)
                                    {
                                        printf("%s\n", buffer[i]);
                                    }
                                }
                            }
                            else if (strcmp(extract, "discover") == 0)
                            {
                                discovery(vrinda, extract, home_directory);
                            }
                            else if (strcmp(extract, "echo") == 0)
                            {
                                // printf("HI\n");
                                //  actual_out
                                echo_p(extract, vrinda);
                            }
                            else
                            {
                                foreground(vrinda);
                                // printf("Command Not Found:\n");
                                continue;
                            }
                            // dup2(actual_out,STDOUT_FILENO);
                            // dup2(a,1);
                        }
                        else if (flagg == 2)
                        {
                            char file_name[500];
                            int l = 0;
                            int chmod(const char *path, mode_t mode);
                            strcpy(file_name, &copy[0][encounter_index + 1]);

                            int p = 0;
                            int file_desc = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 00644);

                            if (file_desc < 0)
                                printf("Error opening the file\n");

                            // a = dup(1);
                            dup2(file_desc, 1);
                            copy[0] = strtok(input, " \t\n");
                            int i = 0;
                            // while (copy[i] != NULL)
                            // {
                            //     printf("%s ", copy[i]);
                            //     i++;
                            //     copy[i] = strtok(NULL, " \t\n");
                            // }
                            if (extract == NULL)
                            {
                                continue;
                            }
                            if (getcwd(cwd, sizeof(cwd)) == NULL)
                            {
                                perror("Error");
                                return 0;
                            }
                            if (strcmp(extract, "cd") == 0)
                            {
                                cd_(cwd, dcwd, home_directory, extract, prev_dir, home_size, relative_path);
                            }
                            else if (strcmp(extract, "pwd") == 0)
                            {
                                pwd(cwd);
                            }
                            else if (strcmp(extract, "echo") == 0)
                            {
                                // printf("pohoch gye\n");
                                // actual_out
                                echo_p(extract, vrinda);
                            }
                            else if (strcmp(extract, "q") == 0)
                            {
                                FILE *fd2 = fopen("history.txt", "w");
                                if (fd2 == NULL)
                                {
                                    perror("Error: Can't open file\n");
                                }
                                if (z > 20)
                                {
                                    for (int i = z - 20; i < z; i++)
                                    {
                                        fprintf(fd2, "%s\n", buffer[i]);
                                    }
                                }
                                else
                                {
                                    for (int i = 0; i < z; ++i)
                                    {
                                        fprintf(fd2, "%s\n", buffer[i]);
                                    }
                                }
                                fclose(fd2);
                                return 0;
                            }
                            else if (strcmp(extract, "ls") == 0)
                            {
                                ls_(vrinda, extract);
                            }
                            else if (strcmp(extract, "history") == 0)
                            {
                                // history(extract, vrinda);
                                if (z > 10)
                                {
                                    for (int i = z - 10; i < z; i++)
                                    {
                                        printf("%s\n", buffer[i]);
                                    }
                                }
                                else
                                {
                                    for (int i = 0; i < z; ++i)
                                    {
                                        printf("%s\n", buffer[i]);
                                    }
                                }
                            }
                            else if (strcmp(extract, "discover") == 0)
                            {
                                discovery(vrinda, extract, home_directory);
                            }
                            else if (strcmp(extract, "bg") == 0)
                            {
                                bgfunc(vrinda);
                            }
                            else if (strcmp(extract, "echo") == 0)
                            {
                                // actual_out
                                // printf("hi\n");
                                echo_p(extract, vrinda);
                            }
                            else if (strcmp(extract, "jobs") == 0)
                            {
                                func(vrinda);
                            }
                            else
                            {
                                foreground(vrinda);
                                // printf("Command Not Found:\n");
                                continue;
                            }
                            // dup2(a,1);
                        }
                    }
                    else
                    {
                        if (extract == NULL)
                        {
                            continue;
                        }
                        if (getcwd(cwd, sizeof(cwd)) == NULL)
                        {
                            perror("Error");
                            return 0;
                        }
                        if (strcmp(extract, "cd") == 0)
                        {
                            cd_(cwd, dcwd, home_directory, extract, prev_dir, home_size, relative_path);
                        }
                        else if (strcmp(extract, "pwd") == 0)
                        {
                            pwd(cwd);
                        }
                        else if (strcmp(extract, "echo") == 0)
                        {
                            // printf("maine pass kiya ( %s, %s )\n", extract, vrinda);
                            echo_p(extract, vrinda);
                        }
                        else if ((strcmp(extract, "jobs") == 0))
                        {
                            func(vrinda);
                        }
                        else if (strcmp(extract, "q") == 0)
                        {
                            FILE *fd2 = fopen("history.txt", "w");
                            if (fd2 == NULL)
                            {
                                perror("Error: Can't open file\n");
                            }
                            if (z > 20)
                            {
                                for (int i = z - 20; i < z; i++)
                                {
                                    fprintf(fd2, "%s\n", buffer[i]);
                                }
                            }
                            else
                            {
                                for (int i = 0; i < z; ++i)
                                {
                                    fprintf(fd2, "%s\n", buffer[i]);
                                }
                            }
                            fclose(fd2);
                            return 0;
                        }
                        else if (strcmp(extract, "ls") == 0)
                        {
                            ls_(vrinda, extract);
                        }
                        else if (strcmp(extract, "history") == 0)
                        {
                            // history(extract, vrinda);
                            if (z > 10)
                            {
                                for (int i = z - 10; i < z; i++)
                                {
                                    printf("%s\n", buffer[i]);
                                }
                            }
                            else
                            {
                                for (int i = 0; i < z; ++i)
                                {
                                    printf("%s\n", buffer[i]);
                                }
                            }
                        }
                        else if (strcmp(extract, "discover") == 0)
                        {
                            discovery(vrinda, extract, home_directory);
                        }
                        else if (strcmp(extract, "echo") == 0)
                        {
                            // actual_out
                            echo_p(extract, vrinda);
                        }
                        else if (strcmp(extract, "jobs") == 0)
                        {
                            func(vrinda);
                        }
                        else if (strcmp(extract, "bg") == 0)
                        {
                            bgfunc(vrinda);
                        }
                        else
                        {
                            foreground(vrinda);
                            // printf("Command Not Found:\n");
                            continue;
                        }
                    }
                }

                flag = 1;
                // dup2(a,1);
            }
        }
    }
    // close(fd);
    // printf("HIII\n");
    FILE *fd2 = fopen("history.txt", "w");
    if (fd2 == NULL)
    {
        perror("Error: Can't open file\n");
    }
    if (z > 20)
    {
        for (int i = z - 20; i < z; z++)
        {
            fprintf(fd2, "%s", buffer[i]);
            // fputs(buffer[i],fd);
        }
    }
    else
    {
        for (int i = 0; i < z; ++i)
        {
            fprintf(fd2, "%s", buffer[i]);
            // fputs(buffer[i],fd);
        }
    }
    fclose(fd2);
}
// agar array mei >20 elements hain, toh last 20 elements store in file
// else
// all elements store in file
