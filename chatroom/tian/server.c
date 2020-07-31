#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<signal.h>
#include<mysql.h>
#include<sys/epoll.h>
#include"chat.h"

#define SERV_PORT 8848  
#define LISTENQ 10     
#define MAX_EVENTS 1000
		
void *deal(void *recv_pack_t);
void Exit(PACK *recv_pack);   
void registe(PACK *recv_pack);
void login(PACK *recv_pack);



MYSQL mysql;
pthread_mutex_t mutex;
pthread_cond_t cond;
User *pHead = NULL;
Relation *pStart = NULL;
Recordinfo *pRec = NULL;

int main()
{
	int i=0;
    int optval;
    char need[1000];
	int sock_fd,conn_fd;
	socklen_t len;
    struct sockaddr_in cli_addr,serv_addr;
    pthread_t pid;
    MYSQL_RES *result;
    
    PACK *pack;
    PACK recv_pack; 
    int ret;

    int epfd,nfds;   
    struct epoll_event ev, events[MAX_EVENTS];  
    len = sizeof(struct sockaddr_in);



    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    
    if (mysql_init(&mysql) == NULL) 
    {
        printf("mysql_init(): %s\n", mysql_error(&mysql));
        return -1;
    }

    if (mysql_real_connect(&mysql,"127.0.0.1","root","new_password","chat",0,NULL,0) == NULL) 
    {
        printf("mysql_real_connect(): %s\n", mysql_error(&mysql));
        return -1;
    }
    
    mysql_set_character_set(&mysql,"utf8");

    printf("服务器启动中...\n");

    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd < 0)
        my_err("socket",__LINE__);
    printf("创建套接字...\n");

    optval = 1;
    if(setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int)) < 0)
        my_err("setsockopt",__LINE__);

    memset(&serv_addr,0,len);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock_fd,(struct sockaddr *)&serv_addr,len) < 0)
        my_err("bind",__LINE__);
    printf("绑定端口...\n");

    if(listen(sock_fd,LISTENQ) < 0)
        my_err("listen",__LINE__);
    printf("侦听套接字...\n");

    epfd = epoll_create(MAX_EVENTS);   
    ev.data.fd = sock_fd;              
    ev.events = EPOLLIN;               
    epoll_ctl(epfd, EPOLL_CTL_ADD, sock_fd, &ev); 
    

    printf("服务器启动成功！\n");

    while(1)
    {
        nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);    

        for(i = 0; i < nfds; i++)
        {
            if(events[i].data.fd == sock_fd)
            {
                conn_fd = accept(sock_fd, (struct sockaddr *)&cli_addr,&len);
                printf("Connected: %s, fd is %d\n",inet_ntoa(cli_addr.sin_addr), conn_fd);
                ev.data.fd = conn_fd;               
                ev.events = EPOLLIN;              
                epoll_ctl(epfd, EPOLL_CTL_ADD, conn_fd, &ev);  
                continue;
            }
            else if(events[i].events & EPOLLIN)
            {
                ret = recv(events[i].data.fd, &pack, sizeof(PACK), MSG_WAITALL);
                pack->data.send_fd = events[i].data.fd;

                if(ret < 0)
                {
                    close(events[i].data.fd);
                    perror("revc");
                    continue;
                }
				if (recv_pack.type == EXIT)
				{
					if (send(events[i].data.fd, &recv_pack, sizeof(PACK), 0) < 0)
					{
						my_err("send", __LINE__);
					}
					memset(need, 0, sizeof(need));
                    sprintf(need, "update user_data set user_state = 0 where user_state = 1 and user_socket = %d", events[i].data.fd);
					mysql_query(&mysql, need);
					epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
				}
				if(recv_pack.type==LOGIN)
				{
					memset(need, 0, sizeof(need));
                    sprintf(need, "select *from user_data where nickname = %s", recv_pack.data.send_user);
                    mysql_query(&mysql, need);
                    result = mysql_store_result(&mysql);
                    if (!mysql_fetch_row(result))
					{
                        recv_pack.type = ACCOUNT_ERROR;
                        memset(recv_pack.data.mes, 0, sizeof(recv_pack.data.mes));
                        printf("登录错误\n");
                        strcpy(recv_pack.data.mes, "0");
                        if (send(events[i].data.fd, &recv_pack, sizeof(PACK), 0) < 0) 
						{
                            my_err("send", __LINE__);
                        }
                        continue;
                    }
 		        	memset(need, 0, sizeof(need)); 
 		        	sprintf(need, "update user_data set user_socket = %d where nickname = %s", events[i].data.fd, recv_pack.data.send_user);
 	    	    	mysql_query(&mysql, need); 
				} 
                pack= (PACK*)malloc(sizeof(PACK));
                memcpy(pack, &recv_pack, sizeof(PACK));
                pthread_create(&pid,NULL,deal,(void *)pack);
            }
        }
    }
    close(sock_fd);
    close(epfd);

    return 0;
}


void *deal(void *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
	switch(recv_pack->type)
	{
		case LOGIN:
			login(recv_pack);
			break;
		case REGISTE:
			registe(recv_pack);            
			break;
		dafault:
			break;
	}
}

void registe(PACK *recv_pack_t)
{
	char need[1000];
	PACK *recv_pack = (PACK *)recv_pack_t;
	
	memset(need, 0, sizeof(need));
	sprintf(need, "insert into user_data values(\"%s\",\"%s\",%d,%d)",  recv_pack->data.send_user, recv_pack->data.mes, 0, recv_pack->data.recv_fd);
	mysql_query(&mysql, need);
	memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
    strcpy(recv_pack->data.mes, "1");
    if (send(recv_pack->data.recv_fd, recv_pack, sizeof(PACK), 0) < 0) 
	{
        my_err("send", __LINE__);
    }	
}

void login(PACK *recv_pack_t)
{
	char need[1000];
	PACK *recv_pack = (PACK *)recv_pack_t;
	MYSQL_RES          *result = NULL;
    MYSQL_ROW          row;
    int ret;
	
	memset(need, 0, sizeof(need));
	sprintf(need, "select *from user_data where nickname = %s", recv_pack->data.send_user);
    pthread_mutex_lock(&mutex);	
    ret = mysql_query(&mysql, need);
    
    
    memset(need, 0, sizeof(need));
    sprintf(need, "select *from user_data where nickname = %s", recv_pack->data.send_user);
    mysql_query(&mysql, need);
    result = mysql_store_result(&mysql);
    if (!mysql_fetch_row(result))
	{
        recv_pack->type = ACCOUNT_ERROR;
        memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
        printf("登录错误\n");
        strcpy(recv_pack->data.mes, "0");
        if (send(recv_pack->data.recv_fd, &recv_pack, sizeof(PACK), 0) < 0) 
		{
            my_err("send", __LINE__);
        }
    }
    else
	{
		recv_pack->type = REGISTE;
        memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
        strcpy(recv_pack->data.mes, "1");
        printf("登录成功\n");
        if (send(recv_pack->data.recv_fd, &recv_pack, sizeof(PACK), 0) < 0) 
		{
            my_err("send", __LINE__);
        }
	} 
}
