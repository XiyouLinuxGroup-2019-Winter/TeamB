#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

int main(int argc,char * argv[])
{
    int i;
    pid_t pid;
    for(i = 0;i < 5;i++)
    {
        pid = fork();
        if(pid == 0)
        break;
    }
    /*if(i == 5)
    {
        sleep(5);
        printf("I am parent\n");
    }*/
    else
    {
        sleep(i);
        printf("I am %dth child\n",i+1);
    }
 
    return 0;
}

