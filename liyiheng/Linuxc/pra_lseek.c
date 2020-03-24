#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>


int main(void)
{
	int fd,n;
	char a[]="The practice for lseek!\n";
	char buf[1024];

	fd = open("lseek.txt",O_RDWR|O_CREAT,0644);
	if(fd < 0)
	{
		perror("open error!");
		exit(1);
	}

	write(fd,a,strlen(a));
  

        lseek(fd,0,SEEK_SET);

	while(n = read(fd,buf,1))
	{
	
	      if(n < 0)
	      {
	         perror("read error!");
	         exit(1);
			    
              }
	  write(STDOUT_FILENO,buf,n);
	}



	close(fd);
	return 0;
}



