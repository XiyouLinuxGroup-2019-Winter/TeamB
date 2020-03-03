/*************************************************************************
	> File Name: my_ls.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月29日 星期六 19时49分53秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/limits.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
//采用二进制思想解析参数
#define PARAM_NONE 0
#define PARAM_A 1
#define PARAM_L 2
#define PARAM_R 4
#define MAXROWLEN 80
int g_leave_len =MAXROWLEN;
int g_maxlen;
int main(int argc,char **argv)
{
    int k=0;
    int num=0;
    char param[32];
    int flag_p=PARAM_NONE;
    //记录参数
    for(int i=1,i<argc,i++){
        if(argv[i][0]=='-'){
            for(int j=0;j<strlen(argv[i]);j++){
                param[k]=argv[i][j];
                k++;
            }
        num++;//记录选项参数个数，方便确认是否指定目录
        }
    }
    //将参数转化为数字标记
    for(int i=0;i<k;i++){
        if(param[i]=='a'){
            flag_p[i]|=PARAM_A;
            continue;
        }
        else if(param[i]=='l'){
            flag_p[i]|=PARAM_L;
            continue;
        }
        else if(param[i]=='R'){
            flag_p[i]|=PARAM_R;
            continue;
        }
    }
    param[k]=0;
    char path[PATH_MAX+1];//储存目录名
    //若未指定目录则执行
    if(num==argc-1){
        strcpy(path,"./");
        path[2]=0;
        display_dir(flag_p,path);
        return 0;
    }
}
void display_dir(int flag_p,char *path)
{
    //打开目录
    DIR *dir;
    if((dir=opendir(path))==NULL){
        my_err("opendir",_LINE_);
    }
    //获取该目录下文件总数和最长文件名的长度
    struct dirent *ptr;
    int count=0;
    while((ptr=readdir(dir))!=NULL){
        if(g_maxlen<strlen(ptr->d_name)){
            g_maxlen=strlen(ptr->d_name);
        }
        count++;
    }
    closedir(dir);
    //获取该目录下所有文件名并与其路径名储存
    char f_names[256][PATH_MAX+1];
    int path_len=strlen(path);
    if((dir=opendir(path))==NULL){
        my_err("opendir",_LINE_);
    } 
    for(int i=0;i<count;i++){
        ptr=readdir(dir);
        strncpy(f_names[i],path,path_len);
        f_names[i][path_len]=0;
        strcat(f_names[i],ptr->d_name);
        f_names[i][path_len+strlen(ptr->d_name)]=0;
    }
    closedir(dir);
    //使用冒泡法对文件名排序
    for(int i=0;i<count-1;i++){
        for(int j=0;j<conut-1;j++){
            if(strcmp(f_names[j],f_names[j+1])>0){
                char temp[PATH_MAX+1];
                strcpy(temp,f_names[j]);
                temp[strlen(f_names[j])]=0;
                strcpy(f_names[j],f_names[j+1]);
                f_names[j][strlen(f_names[j+1])]=0;
                strcpy(f_names[j+1],temp);
                f_names[j+1][strlen(temp)]=0;
            }
        }
    }
    //遍历所有文件名并调用函数
    for(int i=0;i<count;i++){
        display(flag_p,f_names[i]);
    }
}
void display(int flag,char *pathname)
{
    //从路径名中解析出文件名
    int j=0;
    char name[NAME_MAX+1];
    for(int i=0;i<strlen(pathname);i++){
        if(pathname[i]=='/'){
            j=0;
            continue;
        }
        name[j++]=pathname[i];
    }
    name[j]=0;
    //获取文件信息并储存
    struct stat buf;
    if(lstat(name,&buf)==-1){
        my_err("stat",_LINE_);
    }
    //根据命令参数调用不同函数打印文件信息
    switch(flag){
        case PARAM_NONE :
            if(name(0)!='.'){
                print_fname(name);
            }
            break;
        case PARAM_A :
            print_fname(name);
            break;
        csae PARAM_L :
            if(name[0]!='.'){
                print_finfo(buf,name);
                printf("  %-s\n",name);
            }
            break;
        case PARAM_R :
            
        case PARAM_A+PARAM_L :
            print_finfo(buf,name);
            printf("  %-s\n",name);
            break;
        case PARAM_A+PARAM_R :
        case PARAM_L+PARAM_R :
        case PARAM_A+PARAM_L+PARAM_R :
    }
}
void print_fname(char *name)
{
    //判断如果本行是否有空间打印
    if(g_leave_len<g_maxlen){
        printf("\n");
        g_leave_len=MAXROWLEN;
    }
    //对齐得输出
    int len=g_maxlen-strlen(name);
    printf("%s",name);
    for(int i=0;i<len;i++){
        printf(" ");
    }
    printf("  ");
    //实时记录行剩余空间
    g_leave_len-=(g_maxlen+2);
}
void print_finfo(struct stat buf,char *name)
{
    
}
