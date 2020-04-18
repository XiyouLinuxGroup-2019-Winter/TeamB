#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sys/wait.h>

int main(int argc,char * argv[])
{

    pid_t pid,wpid;
    pid=fork();

    int status;

    if(pid == 0)
    {
        printf("child,my ID = %d,my parent ID = %d\n",getpid(),getppid());
        sleep(10);
        printf("child die\n");
        return  99;
    }
    else if(pid > 0)
    {
       wpid = wait(&status);//如果子进程未终止，父进程阻塞在这个函数上
       // wpid = wait(NULL);//父进程不关心子进程结束原因
        if(wpid == -1)
        {
            perror("wait error\n");
            exit(1);
        }
        if(WIFEXITED(status))//为真，说明子进程正常终止
        printf("child exit with %d\n",WEXITSTATUS(status));

        if(WIFSIGNALED(status))//为真，说明子进程是被信号终止
         printf("child kill with signal %d\n",WTERMSIG(status));

        printf("----------parent wait child,wpid = %d\n",wpid);
    }
    else 
    {
        perror("fork error\n");
        exit(1);
    }

   
    return 0;
}

