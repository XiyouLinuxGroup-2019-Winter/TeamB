#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

int main(int argc,char * argv[])
{
    printf("before fork 1----\n");
    printf("before fork 2----\n");
    printf("before fork 3----\n");
    printf("before fork 4----\n");
    

    pid_t pid=fork();
    if(pid == -1)
    {
        perror("creat fail\n");
    }
    else if(pid == 0)
    {
        printf("---------child created,pid = %d,parent_pid=%d\n",getpid(),getppid());
    }
    else if(pid > 0)
    {
        printf("-------parent succeed,my child is %d,%d,%d\n ",pid,getpid(),getppid());
    }

    printf("=========end of file\n");
    return 0;
}

