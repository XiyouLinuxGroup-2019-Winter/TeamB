#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "Linklist.h"

#define PORT 8888

#define SUCCESS    1024     


#define LOGIN       0     	//登陆
#define SIGNIN      1      	//注册
#define	CHAT        3      	//聊天
#define ONLINEINFOCHECK  4  //用户是否在线
#define ADDFRIEND   7       //添加好友
#define QUIT        8       //退出
#define NOUSER      9       //没有用户
#define WHISPER     12      //私聊
#define ALREADY     14
#define DELFRIEND   15
#define DELNOUSER   16
#define NOTFRIEND   18
#define LOAD        19

struct UserInfo
{
	int Flag;
	char ID[24];
	char nickname[24];
	char passwd[24];
};

struct UserLogin
{
	int Flag;
	char ID[24];
	char passwd[24];
};

struct ChatInfo
{
	int Flag;
	char ToId[24];
	char MyId[24];
	char Message[512];
	char fileData[100000];
};

struct OnlineUser
{
	char ID[24];
	char nickname[24];
};

struct OnlineInfo
{
	int Flag;
	int Max;
	struct OnlineUser users[20];
};

struct UnKnown
{
	int Flag;
	int data[100000];
};


#endif
