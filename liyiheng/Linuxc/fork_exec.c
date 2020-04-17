#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

int main(int argc,char * argv[])
{

    pid_t pid=fork();
    if(pid == -1)
    {
        perror("creat fail\n");
    }
    else if(pid == 0)
    {
       //execlp("ls","ls","-l","-h",NULL);
       //execlp("date","date",NULL);
        execl("./b.out","b.out",NULL);
        perror("execlp error\n");
        exit(1);
    }
    else if(pid > 0)
    {
        sleep(1);
        printf("-------parent succeed,my child is %d\n ",pid);
    }

   
    return 0;
}

