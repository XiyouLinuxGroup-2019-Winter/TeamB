#include<stdio.h>
#include<pwd.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<unistd.h>
#include<Linux/limits.h>
#include<dirent.h>
#include<grp.h>
#include<errno.h>

#define PARAM_NONE  0
#define PARAM_A     1
#define PARAM_L     2
#define MAXROWLEN   80

int g_leave_len = MAXROWLEN;
int g_maxlen;

void my_err(const char *err_string,int line)
{
	fprintf(stderr,"line:%d",line);
	perror(err_string);
	exit(1);
}


void display_attribute(struct stat buf,char * name)
{
	char buf_time[32];
	struct passwd  *psd;
	struct group *grp;

	if(S_ISLNK(buf.st_mode))
	{
		printf("1");
	}
	else if(S_ISREG(buf.st_mode))
	{
		printf("-");
	}
	else if(S_ISDIR(buf.st_mode))
	{
		printf("d");
	}
	else if(S_ISCHR(buf.st_mode))
	{
		printf("c");
	}
	else if(S_ISBLK(buf.st_mode))
	{
		printf("b");
	}
	else if(S_ISFIFO(buf.st_mode))
	{
		printf("f");
	}
	else if(S_ISSOCK(buf.st_mode))
	{
		printf("s");
	}


	if(buf.st_mode & S_IRUSR)
	{
		printf("r");
	}
	else
		printf("-");

	if(buf.st_mode & S_IWUSR)
	{
		printf("w");
	}
	else
		printf("-");

	if(buf.st_mode & S_IXUSR)
	{
		printf("x");
	}
	else
		printf("-");



	if(buf.st_mode & S_IRGRP)
	{
		printf("r");
	}
        else
		printf("-");

	if(buf.st_mode & S_IWGRP)
	{
		printf("w");
	}
	else
		printf("-");

	if(buf.st_mode & S_IXGRP)
	{
		printf("x");
	}
	else
		printf("-");


	if(buf.st_mode & S_IROTH)
	{
		printf("r");
	}
	else
		printf("-");

	if(buf.st_mode & S_IWOTH)
	{
		printf("w");
	}
	else
		printf("-");

	if(buf.st_mode & S_IXOTH)
	{
		printf("x");
	}
	else
		printf("-");

	printf("     ");


        psd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	printf("%4d",buf.st_nlink);
	printf("%-8s",psd->pw_name);
	printf("%-8s",grp->gr_name);

	printf("%6d",buf.st_size);
	strcpy(buf_time,ctime(&buf.st_mtime));
	buf_time[strlen(buf_time)-1] = '\0';
	printf("%s",buf_time);
}


