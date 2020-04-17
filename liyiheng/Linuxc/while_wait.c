#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sys/wait.h>

int main(int argc,char * argv[])
{
    int i;
    pid_t pid,wpid;
    for(i = 0;i < 5;i++)
    {
        pid = fork();
        if(pid == 0)
        break;
    }
    if(i == 5)
    {
        while((wpid = waitpid(-1,NULL,0)))
              {
                  printf("wait child %d\n",wpid);
              }
        sleep(5);
        printf("I am parent\n");
    }
    else
    {
        sleep(i);
        printf("I am %dth child\n",i+1);
    }
 
    return 0;
}

