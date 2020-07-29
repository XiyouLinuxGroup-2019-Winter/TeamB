/*************************************************************************
	> File Name: client.h
	> Author: 
	> Mail: 
	> Created Time: 2020年07月28日 星期二 16时49分42秒
 ************************************************************************/

#ifndef _CLIENT_H
#define _CLIENT_H
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
#include<pthread.h>
#include<errno.h>

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
};

typedef struct {
    char type[2];
    char len[2];
    char data[1024];
}Pack;
char user_id[10];

int print_main();
int print_login();
int uregister(int connfd);
int send_pack(int connfd,int type,int len,char *value);
int my_write(int connfd,char *send_buf,int len);
int my_read(int conn_fd,void *buf,int len);
int unpack(int connfd,char *recv_buf,int lenth);
void my_err(const char *str,int line);
int login(int connfd);

#endif
