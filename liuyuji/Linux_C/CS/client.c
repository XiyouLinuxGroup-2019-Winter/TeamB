/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月11日 星期六 23时56分18秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"my_recv.h"
#define INVALID_USERINFO 'n'
#define VALID_USERINFO 'y'

int get_userinfo(char *buf,int len)
{
    if(buf==NULL){
        return -1;
    }
    int i=0,ch;
    while(((ch=getchar())!='\n') && (ch!=EOF) && (i<len-2)){
        buf[i++]=ch;
    }
    buf[i++]='\n';
    buf[i++]=0;
    //printf("%s",buf);//zzz
    return 0;
}
void send_userinfo(int conn_fd,const char* str)
{
    int ret=0;
    char send_buf[32],recv_buf[32];
    do{
        printf("%s :",str);
        if(get_userinfo(send_buf,32)<0){
            printf("error return\n");
            exit(1);
        }
        //printf("%d\n",strlen(send_buf));//zzz
        if(send(conn_fd,(void *)send_buf,strlen(send_buf),0)<0){
            my_err("send",__LINE__);
        }
        if(ret=recv(conn_fd,recv_buf,sizeof(recv_buf),0)<0){
            printf("%d:date is too long\n",__LINE__);
        }
        if(recv_buf[0]==VALID_USERINFO){
            break;
        }
        else{
            printf("%s error\n",str);
        }
    }while(1);
}
int main(int argc,char **argv)
{
    struct sockaddr_in serv_addr;
    int conn_fd,ret;
    int serv_port;
    char recv_buf[1024];
    memset(recv_buf,0,sizeof(recv_buf));
    //检查参数个数
    if(argc!=5){
        printf("Usage: [-p] [serv_port] [-a] [serv_addr]\n");
        exit(1);
    }
    //初始化服务器地址
    memset(&serv_addr,0,sizeof(struct sockaddr_in));
    serv_addr.sin_family=AF_INET;
    //解析参数，获取服务器地址以及端口号
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"-p")==0){
            serv_port=atoi(argv[i+1]);
            //检查参数合法性并记录
            if(serv_port<0 || serv_port>65535){
                printf("invalid serv_port\n");
                exit(1);
            }
            else{
                serv_addr.sin_port=htons(serv_port);
            }
            continue;
        }
        if(strcmp(argv[i],"-a")==0){
            if(inet_aton(argv[++i],&serv_addr.sin_addr)==0){
                printf("invaild serv_addr\n");
                exit(1);
            }
            continue;
        }
    }
    //再次检查参数是否正确
    if(serv_addr.sin_port==0 || serv_addr.sin_addr.s_addr==0){
        printf("Usage: [-p] [serv_port] [-a] [serv_addr]\n");
        exit(1);
    }
    //创建TCP套接字
    conn_fd=socket(AF_INET,SOCK_STREAM,0);
    if(conn_fd<0){
        my_err("socket",__LINE__);
    }
    //链接服务器
    if(connect(conn_fd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr_in))<0){
        my_err("connect",__LINE__);
    }
    //向服务器发送信息
    send_userinfo(conn_fd,"username");
    send_userinfo(conn_fd,"password");
    //接收服务器消息
    if((ret=my_recv(conn_fd,recv_buf,sizeof(recv_buf)))<0){
        my_err("recv",__LINE__);
    }
    printf("ret=%d\n",ret);//
    //printf("%d\n",strlen(recv_buf));
    for(int i=0;i<ret;i++){
        //printf("666\n");//
        printf("%c",recv_buf[i]);
        //printf("666\n");//
    }
    printf("\n");
    close(conn_fd);
    return 0;
}
