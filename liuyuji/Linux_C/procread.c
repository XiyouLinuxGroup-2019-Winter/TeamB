/*************************************************************************
	> File Name: procread.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月15日 星期三 09时53分37秒
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
    char buf[20];
    umask(0);
    fd=open(FIFO_PATH,O_RDONLY);
    read(fd,buf,20);
    printf("read:%s\n",buf);
    close(fd);
    exit(0);
}
