/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月27日 星期一 19时34分28秒
 ************************************************************************/

#include"chat.h"
FILE* log=fopen("log","w");
void setnoblock(int sock)
{
    int flag=fcntl(sock,F_GETFL);
    if(ops<0){
        my_err("fcntl",__LINE__);
        exit(1);
    }
    flag|=O_NONBLOCK;  
    if(fcntl(sock,F_SETFL,flag)<0)  
    {  
        my_err("fcntl(sock,SETFL,opts)",__LINE__);  
        exit(1);  
    }
}
void *unpack(void *arg)
{
    int conn_fd=*(int *)arg;
    
    //接收数据类型
    char ty;
    if(my_read(conn_fd,&ty,1)<0){
        my_err("read",__LINE__);
    }
    fprintf(log,"数据type为%c\n",type);
    
    //接收数据长度
    char len;
    if(my_read(conn_fd,&len,1)<0){
        my_err("read",__LINE__);
    }
    fprintf(log,"数据len为%c\n",len);
    
    //接收数据
    char recv_buf[1024];
    memset(recv_buf,0,sizeof(recv_buf));
    if(my_read(conn_fd,recv_buf,atoi(&len))<0){
        my_err("read",__LINE__);
    }
    fprintf(log,"数据为%s\n",recv_buf);
    
    //储存数据
    char *arg=(char *)malloc(atoi(len)+1);
    strncpy(arg,recv_buf,atoi(len));
    arg[atoi(len)]=0;

    //判断type，将对应处理函数放进线程池
    int type=atoi(&ty);
    switch(type){
        case LOGIN:
        add_work(login,(void *)arg);
        break;
        case UREGISTER:
        add_work(uregister,(void *)arg);
        break;
        case FHCAT:
        add_work(fchat,(void *)arg);
        break;
        case ADDFRIEND:
        add_work(addfriend,(void *)arg);
        break;
        case DELFRIEND:
        add_work(delfriend,(void *)arg);
        break;
        case FINDFRIEN:
        add_work(findfriend,(void *)arg);
        break;
        case FRIENDLIST:
        add_work(friendlist,(void *)arg);
        break;
        case FCHATMSG:
        add_work(fchatmsg,(void *)arg);
        break;
        case BLOCKFRIEND:
        add_work(blockfriend,(void *)arg);
        break;
        case GCHAT:
        add_work(gchat,(void *)arg);
        break;
        case CREATEGROUP:
        add_work(creategroup,(void *)arg);
        break;
        case DELGROUP:
        add_work(delgroup,(void *)arg);
        break;
        case ADDGROUP:
        add_work(addgroup,(void *)arg);
        break;
        case EXITGROUP:
        add_work(exitgroup,(void *)arg);
        break;
        case GROUPMEMBER:
        add_work(groupmember,(void *)arg);
        break;
        case GCHATMSG:
        add_work(gchatmsg,(void *)arg);
        break;
        case SETSTATE:
        add_work(setstate,(void *)arg);
        break;
        case DELMEMBER:
        add_work(delmember,(void *)arg);
        break;
    }
}
int my_read(int conn_fd,void *buf,int len)
{
    int nleft=len;
    int nread=0;
    char *bufp=buf;
    //循环读数据
    while(nleft>0){
        if((nread=read(conn_fd,bufp,nleft))==-1){
            if(errno==EAGAIN){
                nread=0;
            }else{
                return -1;
            }
        }else if(nread==0){
            continue;
        }
        nleft-=nread;
        bufp+=nread;
    }

    return (len-nleft);
}
int main()
{
    //初始化服务器TCP套接字
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
    fprintf(log,"listen socket %d had been done\n",listenfd);


    MYSQL mysql;
    //初始化数据库
    if(NULL == mysql_init(&mysql)){
		my_err("mysql_init", __LINE__);
	}
    if(mysql_library_init(0, NULL, NULL) != 0){
		my_err("mysql_library_init", __LINE__);
	}
    //连接数据库
    if(NULL == mysql_real_connect(&mysql, "127.0.0.1", "root", "Lyj011007.", "chatroom", 0, NULL, 0)){
		my_err("mysql_real_connect", __LINE__);
	}
	//设置中文字符集
	if(mysql_set_character_set(&mysql, "utf8") < 0){
		my_err("mysql_set_character_set", __LINE__);
	}
	fprintf(log,"连接mysql数据库成功!\n");

    //初始化线程池
    pool_init(6);
    
    //初始化epoll
    int epfd=epoll_create(20);
    if(epfd<0){
        my_err("epoll_create",__LINE__);
    }
    struct epoll_event ev;
    
    //将epoll设置为ET模式
    ev.events=EPOLLIN | EPOLLET;
    ev.data.fd=listenfd;
    
    //将listenfd设置为非阻塞
    setnoblock(listenfd);

    //将listenfd加入到epoll中
    if(epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev)<0){
        my_err("epoll_ctl",__LINE__);
    }

    //处理连接请求
    int event_num=0;
    struct sockaddr_in client_addr;
    struct epoll_event ep_events[20];
    int client_addr_len=sizeof(struct sockaddr);
    int conn_fd;
    while(1){
        event_num=epoll_wait(epfd,ep_events,20,-1);
        for(int i=0;i<event_num;i++){
            //若有客户端连接
            if(ep_events[i].data.fd==listenfd){
                if((conn_fd=accept(listenfd,(struct sockaddr*)&client_addr,&client_addr_len))<0){
                    my_err("accept",__LINE__);
                }
                fprintf(log,"client %s connect\n",inet_ntoa(client_addr));
                //设置为非阻塞
                setnoblock(connfd);
                
                ev.data.fd=conn_fd;
                ev.events=EPOLLIN | EPOLLET | EPOLLHUP;
                epoll_ctl(epfd,EPOLL_CTL_ADD,conn_fd,&ev);
            }
            else if(ev.events[i].events & EPOLLIN){
                add_work(unpack,&ev.events[i].data.fd);
            }
        }
    }

}
