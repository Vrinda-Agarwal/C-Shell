#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <dirent.h>
#include "echo.h"
// int actual_out was there
void echo_p(char *extract, char *input)
{
    char *echop[100];
    for( int i=0; i<100; i++ )
        echop[i] = (char *)malloc(sizeof(char)*100);

    char *copyy[200];
    copyy[0] = (char *)malloc(sizeof(char)*500);
    strcpy(copyy[0], input);
    
    int j,indd=0;
    while (copyy[0][j] != '\0')
    {
        if (copyy[0][j] == '>')
        {
            indd = j;
            break;
        }
        j++;
    }
    //printf("%d\n",indd);
    if( indd != 0 )
        copyy[0][indd]='\0';
    // printf("%s\n",copyy[0]);
    strcpy(echop[0],copyy[0]);
    echop[0] = strtok(copyy[0], " \t\n");
    // printf("%s\n",echop[0]); 
    int i = 0;
    while (echop[i] != NULL)
    {
        //printf("Hi\n");
        if( i!=0 )
            printf("%s ", echop[i]);
        i++;
        echop[i] = strtok(NULL, " \t\n");
        // printf("%s ", echop[i]);
    }
    printf("\n");
}
