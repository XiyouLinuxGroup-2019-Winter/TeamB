#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

int main()
{
    int ret;
    int fd[2];
    pid_t pid;

    ret = pipe(fd);
    char *str = "hello\n";
    char buf[4096];
    if(ret == -1)
    {
        perror("error\n");
    }

    pid = fork();
    if(pid > 0)
    {
        close(fd[0]);
        write(fd[1],str,strlen(str));
        sleep(1);
        close(fd[1]);
    }

    else if(pid == 0)
    {
        close(fd[1]);
        ret = read(fd[0],buf,sizeof(buf));
        write(STDOUT_FILENO,buf,ret);
        close(fd[0]);
    }
}

