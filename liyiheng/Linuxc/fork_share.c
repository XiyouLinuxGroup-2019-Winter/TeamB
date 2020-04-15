#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int a = 100;

int main()
{
    pid_t pid;
    pid = fork();
    if(pid == -1)
    {
        perror("fork error\n");
        exit(1);
    }
    else if(pid == 0)
    {
        a = 200;
        printf("I am child,pid = %d,ppid = %d\n",getpid(),getppid());
        printf("child a = %d\n",a);
    }
    else if(pid > 0)
    {
        a = 299;
        printf("I am parent,pid = %d,ppid = %d\n",getpid(),getppid());
        printf("parent a = %d\n",a);
    }

    printf("----------finish\n");
    return 0;
           
}

