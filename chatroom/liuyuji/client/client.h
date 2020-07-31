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

char user_id[10];//用户id
int connfd;//socket
int chat_flag;//聊天标志1好友2群
char chat_id[10];//聊天对象
int read_len;

int send_pack(int connfd,int type,int len,char *value);
int unpack(int connfd,char *recv_buf,int lenth);
int my_write(int connfd,char *send_buf,int len);
int my_read(int conn_fd,void *buf,int len);
void my_err(const char *str,int line);

void *msgbox(void *arg);
int get_arg(char *read_buf,char *recv_buf,int len);

int print_main();
int login();
int uregister();
int print_meau();
int print_friend();
int addfriend();


#endif
