#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	int fd;
	int ret;
	char *p = "I like Linux!\n";
        char *p2 = "after write somethig!\n";

	fd = open("practice.txt",O_RDWR|O_CREAT|O_TRUNC,0644);
	if(fd<0)
	{
		perror("open error!");
		exit(1);
	}
         

	ret = write(fd,p,strlen(p));
	if(ret<0)
	{
		perror("write error!");
	}

	else
		printf("write success!\n");

	ret = write(fd,p2,strlen(p2));
	if(ret <0)
	{
		perror("write error!");
	}
	else
		printf("please Enter anykey countine!");

	getchar();

	close(fd);


        ret = unlink("practice.txt");
	if(ret<0)
	{
		perror("unlink error!");
		exit(1);
	}
     
	return 0;
}

