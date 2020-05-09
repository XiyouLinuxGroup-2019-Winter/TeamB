#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<sys/mman.h>
#include<fcntl.h>

struct student{
    int id;
    char name[256];
    int age;
}*p;

int main()
{
    struct student stu = {1,"yjy",19};
    struct student *p;
    int fd;
    fd = open("text_map",O_RDWR|O_CREAT|O_TRUNC,0644);

    if(fd < 0)
    {
        perror("open error\n");
    }


    ftruncate(fd,sizeof(stu));

    p = mmap(NULL,sizeof(stu),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

    if(p == MAP_FAILED)
    {
        perror("mmap error\n");
    }
    
    while(1)
    {
        memcpy(p,&stu,sizeof(stu)); 
        stu.id++;
        sleep(1);
    }

    munmap(p,sizeof(stu));

    close(fd);
}




