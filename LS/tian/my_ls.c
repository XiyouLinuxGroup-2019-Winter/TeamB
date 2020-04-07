#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<linux/limits.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>

#define PARAM_NONE   0                 //无参数
#define PARAM_A      1                 //-a  显示所有文件
#define PARAM_L      2                 //-l  显示一个文件的详细信息
#define PARAM_R      8                 //-R  
#define MAXROWLEN    80                //一行显示的最多字符数

int g_leave_len = MAXROWLEN;           
int g_maxlen;                          

unsigned long long sum; 

/*错误处理函数*/
void my_err(const char *err_string,int line)
{
	fprintf(stderr, "line:%d ", line);
	perror(err_string);
	exit(1);
}


/*获取文件属性并打印*/
void display_attribute(struct stat buf,char *name)
{
	char buf_time[32];
	struct passwd *psd;
	struct group *grp;

/*文件类型*/
	if(S_ISLNK(buf.st_mode))
	{
		printf("l");
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

/**/
	if(buf.st_mode&S_IRUSR)
	{
		printf("r");
	}
	else
	{
		printf("-");
	}
	if(buf.st_mode&S_IWUSR)
        {
                printf("w");
        }
        else
        {
                printf("-");
        }
	if(buf.st_mode&S_IXUSR)
        {
                printf("x");
        }
        else
        {
                printf("-");
        }

/**/
	if(buf.st_mode&S_IRGRP)
	{
		printf("r");
	}
	else
	{
		printf("-");
	}
	if(buf.st_mode&S_IWGRP)
        {
                printf("w");
        }
        else
        {
                printf("-");
        }
	if(buf.st_mode&S_IXGRP)
        {
                printf("x");
        }
        else
        {
                printf("-");
        }

/**/
	if(buf.st_mode&S_IROTH)
	{
		printf("r");
	}
	else
	{
		printf("-");
	}
	if(buf.st_mode&S_IWOTH)
        {
                printf("w");
        }
        else
        {
                printf("-");
        }
	if(buf.st_mode&S_IXOTH)
        {
                printf("x");
        }
        else
        {
                printf("-");
        }

	printf("        ");

        /*通过uid与gid获取文件所有者的用户名和组名*/
	psd=getpwuid(buf.st_uid);
	grp=getgrgid(buf.st_gid);
	printf("%4ld ",buf.st_nlink);   //打印文件链接数
	printf("%-8s",psd->pw_name);    //打印用户名字
	printf("%-8s",grp->gr_name);    //打印用户组名字

	printf("%6ld  ",buf.st_size);     //打印文件大小
	sum = sum + buf.st_size;
	strcpy(buf_time,ctime(&buf.st_mtime));
	buf_time[strlen(buf_time)-1]='\0';//去掉换行符
}



//输出文件名若命令无-l，输出要上下对齐
void display_single(char *name)
{
	int i,len;
        //空间不足，进行换行
	if(g_leave_len<g_maxlen)
	{
		printf("\n");
		g_leave_len=MAXROWLEN;
	}

	len=g_maxlen-strlen(name);
	printf(" %-s",name);

	for(i=0;i<len;i++)
	{
		printf(" ");
	}
	printf(" ");
	//下面两指示空两格
	g_leave_len -=(g_maxlen+2);
}



//根据命令行输出文件信息
void display(int flag,char *pathname)
{
	int i,j;
	struct stat buf;
	char  name[NAME_MAX+1];

	//解析文件名
	for(i=0,j=0;i<strlen(pathname);i++)
	{
		if(pathname[i]=='/')
		{
			j=0;
			continue;
		}
		name[j++]=pathname[i];
	}
	name[j]='\0';

	//解析链接文件
	if(lstat(pathname,&buf)==-1)
	{
		my_err("stat",__LINE__);
	}

	switch(flag)
	{
		case PARAM_NONE:                                     //无选项
			if(name[0]!='.')
			{
				display_single(name);
			}
			break;

		case PARAM_A:                                        // -a
                        display_single(name);
                        break;

		case PARAM_L:                                        // -l
                        if(name[0]!='.')
                        {
                                display_attribute(buf,name);
				printf("%-s\n",name);
                        }
                        break;

		case PARAM_R:                                        // -R
                      if(name[0]!='.') 
		      {
			      display_single(name);
		      }
                       break;

		case PARAM_A+PARAM_L:                                // -a与-l
                        display_attribute(buf,name);
			printf("%-s\n",name);
                        break;

		case PARAM_A+PARAM_R:                                // -a与-R
                        display_single(name);
                        printf("%-s\n",name);
                        break;

		case PARAM_R+PARAM_L:                                //-R与-l
                        if(name[0]!='.')
                        {
                                display_attribute(buf,name);
                                printf("%-s\n",name);
                        }
                        break;

		case PARAM_A+PARAM_L+PARAM_R:                        //-a与-R与-l
                        display_attribute(buf,name);
                        printf("%-s\n",name);
                        break;

		default:
			break;
	}
}

//显示目录信息
void display_dir(int flag_param,char *path)
{
	DIR  *dir;
	struct dirent  *ptr;
	int count=0;
	char filenames[256][PATH_MAX+1],temp[PATH_MAX+10];

	//获取该目录下文件总数与最长的文件名
	dir=opendir(path);
	if(dir==NULL)
	{
		my_err("opendir",__LINE__);
	}
	while((ptr=readdir(dir))!=NULL)
	{
		if(g_maxlen<strlen(ptr->d_name))
		{
			g_maxlen=strlen(ptr->d_name);
		}
		count++;
	}
	closedir(dir);
	if(count>256)
	{
		my_err("too many files under this dir",__LINE__);
	}

	int i,j,len=strlen(path);
	//获取所有文件名
	dir=opendir(path);
	for(i=0;i<count;i++)
	{
		ptr=readdir(dir);
		if(ptr==NULL)
		{
			my_err("readdir",__LINE__);
		}
		strncpy(filenames[i],path,len);
		filenames[i][len]='\0';
		strcat(filenames[i],ptr->d_name);
		filenames[i][len+strlen(ptr->d_name)]='\0';

	}
	

	//冒泡排序
	//按文件名
	for(i=0;i<count-1;i++)
	{
		for(j=0;j<count-1-i;j++)
		{
			if(strcmp(filenames[j],filenames[j+1])>0)
			{
				strcpy(temp,filenames[j+1]);
				temp[strlen(filenames[j+1])]='\0';
				strcpy(filenames[j+1],filenames[j]);
				filenames[j+1][strlen(filenames[j])]='\0';
				strcpy(filenames[j],temp);
				filenames[j][strlen(temp)]='\0';
			}
		}
	}
	sum = 0;
	for(i=0;i<count;i++)
	{
		display(flag_param,filenames[i]);
	}

	closedir(dir);
	//命令行无-l，打印一个换行符
	if((flag_param&PARAM_L)==0)
	{
		printf("\n");
	}
}



/*主函数*/
int main(int argc,char **argv)
{
	int i,j,k,num;
	char path[PATH_MAX+1];
	char param[32];                        //保存命令行参数
	int flag_param=PARAM_NONE;             //参数种类
	struct stat buf;

	//命令行参数解析
	j=0;
	num=0;
	for(i=0;i<argc;i++)
	{
		if(argv[i][0]=='-')
		{
			for(k=1;k<strlen(argv[i]);k++,j++)
			{
				param[j]=argv[i][k];
			}
			num++;
		}
	}

	//只支持参数a，R，l，其他就报错
	for(i=0;i<j;i++)
	{
		if(param[i]=='a')
		{
			flag_param |=PARAM_A;
			continue;
		}
		else if(param[i]=='l')
		{
			flag_param |=PARAM_L;
			continue;
		}
		else if(param[i]=='R')
                {
                        flag_param |=PARAM_R;
                        continue;
                }
		else
		{
			printf("myls:invalid option -%c\n",param[i]);
			exit(1);
		}
	}
	param[j]='\0';

	//没有输入文件名，就显示当前目录
	if((num+1)==argc)
	{
		strcpy(path,"./");
		path[2] = '\0';
		display_dir(flag_param,path);
		return 0;
	}

	i=0;
	while(i<argc)
	{
		//不是目标文件，解析下一个命令行参数
		if(argv[i][0]=='-')
		{
			i++;
			continue;
		}
		else
		{
			strcpy(path,argv[i]);
			//文件不存在，报错退出程序
			if(stat(path,&buf)==-1)
			{
				my_err("stat",__LINE__);
			}
			if(S_ISDIR(buf.st_mode))
			{
				if(path[strlen(argv[i])-1]!='/')
				{
					path[strlen(argv[i])]!='/';
					path[strlen(argv[i])+1]!='\0';
				}
				else
				{
					path[strlen(argv[i])]!='\0';
				}
				display_dir(flag_param,path);
				i++;
			}
			else
			{
				display(flag_param,path);
				i++;
			}
		}
	}
	return 0;
}
