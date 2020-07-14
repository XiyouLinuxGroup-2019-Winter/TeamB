/*************************************************************************
	> File Name: my_recv.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月14日 星期二 14时37分36秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<stdlib.h>
#include"my_recv.h"

void my_err(const char *str,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(str);
    exit(1);
}
int my_recv(int conn_fd,char *date_buf,int len)
{
    static char recv_buf[1024];
    static char *pread;
    static int len_remain=0;
    int i=0;
    if(len_remain<=0){
        if((len_remain=recv(conn_fd,(void *)recv_buf,sizeof(recv_buf),0))<0){
            my_err("recv",__LINE__);
        }
        else if(len_remain==0){
            return 0;
        }
        pread=recv_buf;
    }
    for(i=0;*pread!='\n';i++){
        if(i>len){
            return -1;
        }
        date_buf[i]=*pread++;
        len_remain--;
    }
    len_remain--;
    pread++;
    return i;
}
