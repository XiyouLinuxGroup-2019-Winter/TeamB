/*************************************************************************
	> File Name: epoll.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月17日 星期五 19时06分03秒
 ************************************************************************/

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <pthread.h>
#include <semaphore.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include"my_recv.h"
#define NAMESIZE 10
#define SERV_PORT 8888
#define MAXLINE 4096
int main()
{
    //创建TCP套接字
    int connfd;
    int listenfd=socket(AF_INET,SOCK_STREAM,0);
    if(listenfd<0){
        my_err("socket",__LINE__);
    }
    //设置套接字可重新绑定端口
    int opt=1;
    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(void *)&opt,sizeof(opt))<0){
        my_err("setsockopt",__LINE__);
    }
    //初始化服务器地址
    struct sockaddr_in listenfd_addr;
    memset(&listenfd_addr,0,sizeof(struct sockaddr_in));
    listenfd_addr.sin_family=AF_INET;
    listenfd_addr.sin_port=htons(SERV_PORT);
    listenfd_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    //绑定服务器地址
    if(bind(listenfd,(struct sockaddr*)&listenfd_addr,sizeof(struct sockaddr))<0){
        my_err("bind",__LINE__);
    }
    //转为监听套接字
    if(listen(listenfd,20)<0){
        my_err("listen",__LINE__);
    }
    //创建epoll句柄
    int epfd=epoll_create(20);
    if(epfd<0){
        my_err("epoll_create",__LINE__);
    }
    struct epoll_event ev;
    ev.events=EPOLLIN;
    ev.data.fd=listenfd;
    //将listenfd加入到epoll中
    if(epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev)<0){
        my_err("epoll_ctl",__LINE__);
    }
    int event_num=0;
    //处理连接请求
    struct sockaddr_in client_addr;
    struct epoll_event ep_events[10];
    char recv_buf[1024];
    int client_addr_len=sizeof(struct sockaddr);
    while(1){
        event_num=epoll_wait(epfd,ep_events,10,500);
        for(int i=0;i<event_num;i++){
            if(ep_events[i].data.fd==listenfd){
                connfd=accept(listenfd,(struct sockaddr*)&client_addr,&client_addr_len);
                if(connfd<0){
                    my_err("accept",__LINE__);
                }
                ev.data.fd=connfd;
                ev.events=EPOLLIN;
                epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
                printf("accept a new client,ip: %s\n",inet_ntoa(client_addr.sin_addr));
            }
            else if(ep_events[i].events & EPOLLIN){
                int ret=0;
                if((ret=recv(ep_events[i].data.fd,(void *)recv_buf,sizeof(recv_buf),0))<0){
                    printf("my_recv,%d",__LINE__);
                }
                recv_buf[ret]=0;
                for(int j=0;j<ret;j++){
                    printf("%c",recv_buf[j]);
                }
            }
        }
    }
}
