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
    struct student stu;
    struct student *p;
    int fd;
    fd = open("text_map",O_RDONLY);

    if(fd < 0)
    {
        perror("open error\n");
    }

    p = mmap(NULL,sizeof(stu),PROT_READ,MAP_SHARED,fd,0);

    if(p == MAP_FAILED)
    {
        perror("mmap error\n");
    }
    
    while(1)
    {
        printf("id = %d,name = %s,age = %d\n",p ->id,p->name,p->age);
        sleep(1);
    }

    munmap(p,sizeof(stu));

    close(fd);
}




