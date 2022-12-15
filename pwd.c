#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <dirent.h>
#include "pwd.h"
void pwd(char cwd[500])
{
    if (getcwd(cwd, 100) == NULL)
    {
        perror("Error");
        exit(0);
    }
    printf("%s\n", cwd);
}
