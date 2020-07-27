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
}

#endif
