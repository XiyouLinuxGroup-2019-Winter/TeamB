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
    char path[PATH_MAX+1];
    //未指定目录
    if(num==argc-1){
        strcpy(path,"./");
        path[2]=0;
        display_dir(flag_p,path);
        return 0;
    }

}
void display_dir(int flag_p,char *path)
{
    
}

