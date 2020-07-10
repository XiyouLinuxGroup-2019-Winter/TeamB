/*************************************************************************
	> File Name: my_server.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月10日 星期五 14时54分28秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>

#define SERV_PORT 4507//服务器端口号
#define LISTENQ 12//链接队列最大长度
#define INVALID_USERINFO 'n'//用户信息无效
#define VALID_USERINFO 'y'//用户信息有效
#define USERNAME 0//用户名
#define PASSWORD 1//密码

int main()
{
    //创建TCP套接字
    sock_fd=socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd<0){
        my_err("socket",__LINE__);
    }
    //设置套接字使之可重新绑定端口
    optval=1;
    if(setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int))<0){
        my_err("setsockopt",__LINE__);
    }
    //初始化服务器端地址结构
    memset(&serv_addr,0,sizeof(struct sockaddr_in));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(SERV_PORT);
    serv_addr.in_addr.s_addr=htonl(INADDR_ANY);
    //套接字绑定到固定端口
    if(bind(sock_fd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr_in))<0){
        my_err("bind",__LINE__);
    }
    //将套接字转为监听套接字
    if(listen(sock_fd,LISTENQ)<0){
        my_err("listen",__LINE__);
    }
    cli_len=sizeof(struct sockaddr_in);
    while(1){
        conn_fd=accept(sock_fd,(struct sockaddr*)&cli_addr,cli_len);
        if(conn_fd<0){
            my_err("accept",__LINE__);
        }
        printf("accept a new client,ip: %s\n",inet_ntoa(cli_addr.sin_addr));
        //创建子进程处理
        if((pid=fork())==0){
            while(1){
                if(ret=recv(conn_fd,recv_buf,sizeof(recv_buf),0)<0){
                    perror("recv",__LINE__);
                    exit(1);
                }
                recv_buf[ret]=0;
                if(flag_recv==USERNAME){
                    
                }
            }
        }
    }
}

