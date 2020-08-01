/*************************************************************************
	> File Name: chat.h
	> Author: 
	> Mail: 
	> Created Time: 2020年07月27日 星期一 17时33分31秒
 ************************************************************************/

#ifndef _CHAT_H
#define _CHAT_H

#include <stdio.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "thread_pool.h"
#include<pthread.h>
#include<errno.h>
#define SERV_PORT 8848//服务器端口号

enum{
    LOGIN=1,
    UREGISTER,
    FCHAT,
    ADDFRIEND,
    DELFRIEND,
    FINDFRIEND,
    FRIENDLIST,
    FCHATMSG,
    BLOCKFRIEND,
    QCHAT,
    CREATEGROUP,
    DELGROUP,
    ADDGROUP,
    EXITGROUP,
    GROUPMEMBER,
    GCHATMSG,
    SETSTATE,
    DELMEMBER,
    OVER,
};

typedef struct{
    char type[2];
    char len[2];
    char data[1024];
}Pack;

MYSQL mysql;
FILE* log;
pthread_key_t key;

void setnoblock(int sock);
void *unpack(void *arg);
int my_read(int conn_fd,void *buf,int len);
int get_arg(char *read_buf,char *recv_buf,int len);
int send_pack(int connfd,int type,int len,char *value);
int my_write(int connfd,char *send_buf,int len);
void my_err(const char *str,int line);

void *login(void *arg);
void *uregister(void *arg);
void *addfriend(void *arg);
void *over(void *arg);
void *friendlist(void *arg);
void *findfriend(void *arg);
void *delfriend(void *arg);
void *blockfriend(void *arg);
void *fchat(void *arg);
/*void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);
void *(void *arg);*/

#endif
