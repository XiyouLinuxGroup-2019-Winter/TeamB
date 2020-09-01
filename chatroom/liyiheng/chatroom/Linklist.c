#include "Linklist.h"
#include "main.h"

int ListInit(Linklist *L)
{
	(*L) = (Linklist)malloc(sizeof(Node));

	if(NULL == *L)
	{
		return 1;
	}

	(*L)->next = NULL;

	return 0;
}

int ChatLinkInit(ChatLink *L)
{
	(*L) = (ChatLink)malloc(sizeof(ChatLinklist));

	if(NULL == *L)
	{
		return 1;
	}
	(*L)->next = NULL;

	return 0;
}

int ListInsert(Linklist L,int pos, int Fd, char *ID)
{
	Linklist p = L;
	Linklist q;
	int j = 1;

	while(p && j < pos)
	{
		p = p->next;
		j++;
	}

	if(!p|| j > pos)
	{
		return 1;
	}

	q = (Linklist)malloc(sizeof(Node));
	q->Fd = Fd;
	sprintf(q->ID, "%s", ID);
	q->next = p->next;
	p->next = q;
	
	return 0;
}

int ChatLinkInsert(ChatLink L, int pos, char *from, char *to, char *message)
{
	ChatLink p = L;
	ChatLink q;
	int j = 1;

	while(p && j < pos)
	{
		p = p->next;
		j++;
	}

	if(!p|| j > pos)
	{
		return 1;
	}

	q = (ChatLink)malloc(sizeof(ChatLinklist));
	sprintf(q->from, "%s", from);
	sprintf(q->to, "%s", to);
	sprintf(q->message, "%s", message);
	q->next = p->next;
	p->next = q;
	return 0;
}	

int ListTraverse(Linklist L)
{
	Linklist p = L;

	if(NULL == L)
	{
		return 1;
	}

	while(p->next)
	{
		p = p->next;
		printf("%d ", p->Fd);
		printf("%s ", p->ID);
		printf("\n");
	}

	return 0;
}

int ChatLinkTraverse(ChatLink L)
{
	ChatLink p = L;

	if(NULL == L)
	{
		return 1;
	}

	while(p->next)
	{
		p = p->next;
		printf("%s 对 %s 说 %s\n", p->from, p->to, p->message);
	}
	return 0;
}

int ListLength(Linklist L)
{
	Linklist p = L;
	int length = 0;

	if(NULL == L)
	{
		return 1;
	}

	while(p->next)
	{
		length++;
		p = p->next;
	}
	return length;
}

int ChatLinkLength(ChatLink L)
{
	ChatLink p = L;
	int length = 0;
	if(NULL == L)
	{
		return 1;
	}
	while(p->next)
	{
		length++;
		p = p->next;
	}
	return length;
}

int ListLocate(Linklist L, char *id)
{
	Linklist p = L;
	int location = 1;

	if(NULL == L)
	{
		return 1;
	}

	while(p->next)
	{
		p = p->next;
		if(!strcmp(id, p->ID))
		{
			return location;
		}
		location++;
	}
	return -1;	
}

int ListLocateFromID(Linklist L, char *ID)
{
	Linklist p = L;
	int location = 1;

	if(NULL == L)
	{
		return 1;
	}

	while(p->next)
	{
		p = p->next;
		if(!strcmp(ID, p->ID))
		{
			return location;
		}
		location++;
	}
	return -1;	
}

int ListLocateFromFD(Linklist L, int FD, int flag)
{
	Linklist p = L;
	int location = 1;

	if(NULL == L)
	{
		return 1;
	}

	while(p->next)
	{
		p = p->next;
		if(FD == p->Fd)
		{
			if (flag == 1)
            	printf("ID = %s  退出了....\n", p->ID);
			return location;
		}
		location++;
	}
	return -1;	
}

int GetElem(Linklist L,int pos,int *Fd, char *ID)
{
	Linklist p = L;
	int j = 1;

	if(NULL == L)
	{
		return 1;
	}

	while(p && j < pos)
	{
		p = p->next;
		j++;
	}

	if(!p || j > pos)
	{
		return 1;
	}
	
	p = p->next;
	*Fd = p->Fd;
	sprintf(ID, "%s", p->ID);
	return 0;
}

int GetChatLink(ChatLink L, int pos, char *from, char *to, char *message)
{
	ChatLink p = L;
	int j = 1;
	if(NULL == L)
	{
		return 1;
	}
	while(p && j < pos)
	{
		p = p->next;
		j++;
	}
	if(!p || j > pos)
	{
		return 1;
	}
	p = p->next;
	sprintf(from, "%s", p->from);
	sprintf(to, "%s", p->to);
	sprintf(message, "%s", p->message);

	return 0;
}

int ListDelete(Linklist L,int pos,int *Fd, char *ID)
{
	Linklist p = L;
	Linklist q;
	int j = 1;

	if(NULL == L)
	{
		return 1;
	}

	while((p->next) && j < pos)
	{
		p = p->next;
		j++;
	}

	while(!(p->next) || j > pos)
	{
		return 1;
	}

	q = p->next;
	*Fd = p->Fd;
	sprintf(ID, "%s", p->ID);
	p->next = q->next;
	free(q);
	
	return 0;
}

int ListClear(Linklist L)
{
	Linklist p = L->next;
	Linklist q;

	if(NULL == L)
	{
		return 1;
	}

	while(p)
	{
		q = p->next;
		free(p);
		p = q;
	}

	L->next = NULL;

	return 0;
}

int ListDestroy(Linklist *L)
{
	if(NULL == *L)
	{
		return 1;
	}

	free(*L);

	(*L) = NULL;

	return 0;

}
