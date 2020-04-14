/*************************************************************************
	> File Name: pipe.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月14日 星期二 20时47分46秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
void read_from_pipe(int fd)
{
    char m[100];
    read(fd,m,100);
    printf("read:%s\n",m);
}
void write_from_pipe(int fd)
{
    char *m="Hallo world";
    write(fd,m,strlen(m)+1);
}
int main()
{
    int fd[2];
    pid_t pid;
    int stat_val;
    pipe(fd);
    pid=fork();
    switch(pid)
    {
        case -1:
            printf("worry\n");
            exit(1);
        case 0:
            close(fd[1]);
            read_from_pipe(fd[0]);
            exit(0);
        default:
            close(fd[0]);
            write_from_pipe(fd[1]);
            wait(&stat_val);
            exit(0);
    }
    return 0;
}
