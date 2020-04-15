/*************************************************************************
	> File Name: my_chmod.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月22日 星期六 19时53分57秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
int main(int argc,char* argv[])
{
    if(argc<3){
        printf("请输入正确的命令");
        exit(0);
    }
    int u,g,o;
    int a=atoi(argv[1]);
    u=a/100;
    o=a%10;
    g=(a-u*100)/10;
    int mode=o+g*8+u*8*8;
    if((chmod(argv[2],mode))==-1){
        printf("chmod error");
    };

}
