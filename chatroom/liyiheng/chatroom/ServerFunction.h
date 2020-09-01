#ifndef _SEVERFUNCTION_H_
#define _SEVERFUNCTION_H_
#include "main.h"

struct USERLOGIN
{
	int i;
	char passwd[24];
};

struct RecvMessage
{
	int sockfd;
	Linklist L;
};

struct root
{
	Linklist L;
	ChatLink P;
};

int Deal(int *fd, fd_set *ReadFd, Linklist L, ChatLink P);
int DealSignin(int *fd, fd_set *ReadFd, struct UnKnown *Recv);
int DealLogin(int *fd, fd_set *ReadFd, struct UnKnown *Recv, Linklist L);
int FindID(void* para, int columnCount, char** columnValue, char** columnName);
int DealOnlineInfo(int *fd, Linklist L);
int DealChat(int *fd, fd_set *ReadFd, struct UnKnown *Recv, Linklist L, ChatLink P);
int DealAddFriend(int *fd, fd_set *ReadFd, struct UnKnown *Recv);
int DealDelFriend(int *fd, fd_set *ReadFd, struct UnKnown *Recv);




#endif
