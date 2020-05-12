#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<pthread.h>

int main()
{
    int fd;
    char* p = NULL;
    int len;

    fd = open("maptxt",O_RDWR|O_CREAT|O_TRUNC,0644);
    if(fd == -1)
    {
        perror("open error\n");
    }

    ftruncate(fd,20);//给文件扩展空间,需要写权限才能拓展

    /*lseek(fd,10,SEEK_END);
      write(fd,"\0",1);//给文件扩展空间*/
    len = lseek(fd,0,SEEK_END);

    p = mmap(NULL,len,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
    if(p == MAP_FAILED)
    {
        perror("map error\n");
    }

    strcpy(p,"hello");
    printf("%s\n",p);

    int ret = munmap(p,len);
    if(ret == -1)
    {
        perror("munmap error\n");
    }

    close(fd);
    return 0;

}


