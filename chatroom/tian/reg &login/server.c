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

#define SERV_PORT  8848  
#define LISTENQ    10     
#define MAX_EVENTS 1000

#define FRIEND    1
#define FRI_BLK   2
#define FRI_WHI   3 
#define GRP       4
#define GRP_OWN   5
#define GRP_ADM   6

#define OFFLINE   0
#define ONLINE    1
#define ONE_CHAT  2
#define MANY_CHAT 3




void *deal(void *recv_pack);
void Exit(PACK *recv_pack);   
void registe(PACK *recv_pack);
void login(PACK *recv_pack);
void look_fri(PACK *recv_pack);    
void get_fri_sta(PACK *recv_pack);  
void add_fri(PACK *recv_pack);      
void del_fri(PACK *recv_pack);    
void shi_fri(PACK *recv_pack);      
void rel_fri(PACK *recv_pack);     
void chat_one(PACK *recv_pack);  
void check_mes_fri(PACK *recv_pack);
void cre_grp(PACK *recv_pack);
void add_grp(PACK *recv_pack);
void out_grp(PACK *recv_pack);
void del_grp(PACK *recv_pack);
void set_grp_adm(PACK *recv_pack);
void kick_grp(PACK *recv_pack);
void check_grp(PACK *recv_pack);
void check_mem_grp(PACK *recv_pack);
void chat_many(PACK *recv_pack);
void check_mes_grp(PACK *recv_pack);
void send_file(PACK *recv_pack); 
void recv_file(PACK *recv_pack);

User *U_read();     
Relation *R_read();         
Recordinfo *RC_read();
void Insert(User *pNew);
void Insert_RC(Recordinfo *pNew);
void Insert_R(Relation *pNew);
void Delete_R(Relation *pNew);

MYSQL mysql;
pthread_mutex_t mutex;
pthread_cond_t cond;
User *pHead = NULL;
Relation *pStart = NULL;
Recordinfo *pRec = NULL;

PACK Mex_Box[100];
int sign;
int book;
File file;

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
    printf("等待客户端的接入中...\n");
    
    User *t = U_read();
    pStart = R_read();
    pRec = RC_read();

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
                ret = recv(events[i].data.fd, &recv_pack, sizeof(PACK), MSG_WAITALL);
                pack->data.send_fd = events[i].data.fd;

                if(ret < 0)
                {
                    close(events[i].data.fd);
                    perror("revc");
                    continue;
                }
                else if(ret == 0)
                {
                    ev.data.fd = events[i].data.fd;
                    while(t)
                    {
                        if(t->fd == ev.data.fd)
                        {
                            t->user_state = OFFLINE;
                            break;
                        }
                        t = t->next;
                    }
                    printf("fd: %d 的客户端退出\n",ev.data.fd);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
                    close(events[i].data.fd);
                    continue;
                }
				if (recv_pack.type == EXIT)
				{
					printf("这里没问题2\n");
					if (send(events[i].data.fd, &recv_pack, sizeof(PACK), 0) < 0)
					{
						my_err("send", __LINE__);
					}
					memset(need, 0, sizeof(need));
                    sprintf(need, "update user_data set user_state = 0 where user_state = 1 and user_socket = %d", events[i].data.fd);
					mysql_query(&mysql, need);
					epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
				}
				printf("准备进入线程\n");
                pack= (PACK*)malloc(sizeof(PACK));
                memcpy(pack, &recv_pack, sizeof(PACK));
                if(pthread_create(&pid,NULL,deal,(void *)pack) != 0)
                    my_err("pthread_create",__LINE__);
            }
        }
    }
    free(pack);
    close(sock_fd);
    close(epfd);
    return 0;
}

void send_pack(int fd, PACK *recv_pack, char *ch)
{
    PACK pack_send;
    memcpy(&pack_send, recv_pack, sizeof(PACK));
    strcpy(pack_send.data.recv_user, pack_send.data.send_user);
    strcpy(pack_send.data.send_user, "server");
    strcpy(pack_send.data.mes, ch);
    printf("%s\n", pack_send.data.mes);
    pack_send.data.recv_fd = pack_send.data.send_fd;
    pack_send.data.send_fd = fd;
    if(send(fd, &pack_send, sizeof(pack_send), 0) < 0)
        my_err("send", __LINE__);
}

void *deal(void *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
	printf("进入线程成功\n");
	printf("recv_pack : %d\n",recv_pack->type);
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
	char ch[5];
	PACK *recv_pack = (PACK *)recv_pack_t;
	int fd = recv_pack->data.recv_fd;
	
	User *t = pHead;
    int flag = 0;
    User *pNew = (User *)malloc(sizeof(User));
    while(t)
    {
        if(strcmp(t->nickname, recv_pack->data.send_user) == 0)
        {
            flag = 1;
            break;
        }
        t = t->next;
    }
    
    printf("注册\n");
    
    
    printf("用户账号\n");
    if(flag == 0)
    {
        strcpy(pNew->nickname, recv_pack->data.send_user);
        strcpy(pNew->password, recv_pack->data.mes);
        pNew->user_state = OFFLINE;
        Insert(pNew);
        t = pHead;
        while(t)
        {
            printf("%s\t%s\t%d\n", t->nickname, t->password, t->user_state);
            t = t->next;
        }
        printf("账号到这里结束\n"); 
        memset(need, 0, sizeof(need));
	    sprintf(need, "insert into user_data values('%s','%s',%d,%d)",  recv_pack->data.send_user, recv_pack->data.mes, 0, recv_pack->data.recv_fd);
        printf("%s\n",need);
    	mysql_query(&mysql, need);
        ch[0] = '1';
    }
    else
        ch[0] = '0';
    
    ch[1] = '\0';
	send_pack(fd, recv_pack, ch);
}

void Insert(User *pNew)
{
    User *t = pHead;
    while(t && t->next != NULL)
        t = t->next;
    t->next = pNew;
    pNew->next = NULL;
}

void login(PACK *recv_pack_t)
{
	
	pthread_t pid1;
    pthread_t pid2;
    PACK *recv_pack = (PACK *)recv_pack_t;
	char ch[5];
    int fd = recv_pack->data.recv_fd;
    int i;

    User *t = pHead;
    int flag = 0;
    while(t)
    {
        if(strcmp(t->nickname, recv_pack->data.send_user) == 0 && strcmp(t->password, recv_pack->data.mes) == 0)
        {
            flag = 1;
            break;
        }
        t = t->next;
    }

    if(flag == 0)
        ch[0] = '0';
    else
    {
        if(t->user_state == OFFLINE)
        {
            ch[0] = '1';
            t->user_state = ONLINE;
            t->fd = recv_pack->data.send_fd;
        }
        else 
            ch[0] = '2';
    }
    ch[1] = '\0';
    printf("登录信息\n");
    printf("%s   %s  %s  %d   %d\n",recv_pack->data.send_user,recv_pack->data.mes,recv_pack->data.recv_user,recv_pack->data.recv_fd,recv_pack->data.send_fd);
    send_pack(fd, recv_pack, ch);
    printf("发送成功你的登录信息\n");
}

User *U_read()
{
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char need[1000];
    int rows;
    int fields;

    User *pEnd, *pNew;

    sprintf(need, "select * from user_data");
    mysql_real_query(&mysql, need, strlen(need));
    res = mysql_store_result(&mysql);
    rows = mysql_num_rows(res);
    fields = mysql_num_fields(res);

    while(row = mysql_fetch_row(res))
    {
        pNew = (User *)malloc(sizeof(User));
        strcpy(pNew->nickname, row[0]);
        strcpy(pNew->password, row[1]);
        pNew->user_state = OFFLINE;
        pNew->next = NULL;
        if(pHead == NULL)
            pHead = pNew;
        else
            pEnd->next = pNew;
        pEnd = pNew;
    }
    return pHead;
}

Relation *R_read()
{
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char need[1000];
    int rows;
    int fields;

    Relation *pEnd, *pNew;

    sprintf(need, "select * from friends");
    mysql_real_query(&mysql, need, strlen(need));
    res = mysql_store_result(&mysql);
    rows = mysql_num_rows(res);
    fields = mysql_num_fields(res);

    while(row = mysql_fetch_row(res))
    {
        pNew = (Relation *)malloc(sizeof(Relation));
        strcpy(pNew->user, row[0]);
        strcpy(pNew->friend_user, row[1]);
        pNew->realtion = row[2][0] - '0';
        pNew->next = NULL;
        if(pStart == NULL)
            pStart = pNew;
        else
            pEnd->next = pNew;
        pEnd = pNew;
    }
    return pStart;
}

Recordinfo *RC_read()
{
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char need[1000];
    int rows;
    int fields;

    Recordinfo *pEnd, *pNew;

    sprintf(need, "select * from chat_messages");
    mysql_real_query(&mysql, need, strlen(need));
    res = mysql_store_result(&mysql);
    rows = mysql_num_rows(res);
    fields = mysql_num_fields(res);

    while(row = mysql_fetch_row(res))
    {
        pNew = (Recordinfo *)malloc(sizeof(Recordinfo));
        strcpy(pNew->send_user, row[0]);
        strcpy(pNew->recv_user, row[1]);
        strcpy(pNew->messages, row[2]);
        pNew->next = NULL;
        if(pRec == NULL)
            pRec = pNew;
        else
            pEnd->next = pNew;
        pEnd = pNew;
    }
    return pRec;
}
