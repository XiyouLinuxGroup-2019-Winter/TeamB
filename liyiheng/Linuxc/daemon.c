#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>

int main()
{
    pid_t pid;
    int ret,fd;
    pid = fork();
    if(pid > 0)
    exit(0);

    pid = setsid();
    if(pid == -1)
    {
        perror("fork error\n");
    }
    ret = chdir("/home");
    if(ret == -1)
    {
        perror("chdir error\n");
    }

    umask(0022);

    close(STDIN_FILENO);
    fd = open("/dev/null",O_RDWR);
    if(fd == -1)
    {
        perror("open error\n");
    }

    
    dup2(fd,STDOUT_FILENO);
    dup2(fd,STDERR_FILENO);

    while(1);


}

