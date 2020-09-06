#ifndef _CLIENTFUNCTION_H_
#define _CLIENTFUNCTION_H_

struct RecvMessage
{
	int sockfd;
	Linklist L;
	ChatLink P;
};

void LOGINInterface();
int Register(int *sockfd);
int Login(int *sockfd, Linklist L, ChatLink P);
int MainChat(int *sockfd, Linklist L, ChatLink P);
void *FunctionRecv(void *arg);
int LookUpOnlineUser(int *sockfd);
int whisper(int *sockfd, Linklist L, ChatLink P);
int DealChat(Linklist L, struct UnKnown *Recved, ChatLink P);
int GroupChat(int *sockfd, Linklist L, ChatLink P);
int delFriend(int *sockfd);

#endif
