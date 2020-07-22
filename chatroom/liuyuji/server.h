/*************************************************************************
	> File Name: server.h
	> Author: 
	> Mail: 
	> Created Time: 2020年07月22日 星期三 14时16分27秒
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H

#include<pthread.h>
#include<mysql/mysql>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<stdlib.h>
#include"my_recv.h"
#define SERV_PORT 8848//服务器端口号

#endif
