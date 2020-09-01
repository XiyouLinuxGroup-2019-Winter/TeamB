#ifndef _LINKLIST_H_
#define _LINKLIST_H_

struct Node
{
	int Fd;
	char ID[24];
	struct Node *next;
};

struct ChatLinklist
{
	char from[24];
	char to[24];
	char message[512];
	struct ChatLinklist *next;
};

typedef struct ChatLinklist ChatLinklist;
typedef ChatLinklist *ChatLink;

typedef struct Node Node;
typedef Node *Linklist;



int ListInit(Linklist *L);
int ChatLinkInit(ChatLink *L);
int ListInsert(Linklist L,int pos, int Fd, char *ID);
int ChatLinkInsert(ChatLink L, int pos, char *from, char *to, char *message);
int ListTraverse(Linklist L);
int ChatLinkTraverse(ChatLink L);
int ListLength(Linklist L);
int ChatLinkLength(ChatLink L);
int ListLocate(Linklist L,char *nickname);
int GetElem(Linklist L,int pos,int *Fd, char *ID);
int GetChatLink(ChatLink L, int pos, char *from, char *to, char *message);
int ListDelete(Linklist L,int pos,int *Fd, char *ID);
int ListClear(Linklist L);
int ListDestroy(Linklist *L);
int ListLocateFromID(Linklist L, char *ID);
int ListLocateFromFD(Linklist L, int FD, int flag);

#endif
