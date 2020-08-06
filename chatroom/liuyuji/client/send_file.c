/*************************************************************************
	> File Name: send_file.c
	> Author: 
	> Mail: 
	> Created Time: 2020年08月06日 星期四 23时44分08秒
 ************************************************************************/

#include<stdio.h>
int send_file()
{
    P_LOCK;
    printf("请输入文件的接收者ID\n");
    P_UNLOCK;
    char fid[10];
    scanf("%s",fid);
    P_LOCK;
    printf("请输入您要发送的文件路径\n");
    P_UNLOCK;
    char filename[1024];
    scanf("%s",filename);
    
}
