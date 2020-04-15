/*************************************************************************
	> File Name: procwrite.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月15日 星期三 09时59分08秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#define FIFO_PATH "/home/liuyuji/myfifo"
int main()
{
    int fd;
    char *buf="Hallo,I am pw";
    umask(0);
    mkfifo(FIFO_PATH,S_IFIFO | 0666);
    fd=open(FIFO_PATH,O_WRONLY);
    write(fd,buf,20);
    close(fd);
    exit(0);
}
