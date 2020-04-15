/*************************************************************************
	> File Name: show_files.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月09日 星期一 15时41分10秒
 ************************************************************************/

#include<stdio.h>
#include"my_ls.h"
int main(int argc,char **argv)
{
    DIR *dir;
    dir=opendir(argv[1]);
    struct dirent *ptr;
    for(int i=0;ptr;i++){
        ptr=readdir(dir);
        printf("%s\n",ptr->d_name);
    }
}
