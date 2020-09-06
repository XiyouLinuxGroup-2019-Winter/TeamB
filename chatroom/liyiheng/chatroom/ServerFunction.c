#include "main.h"
#include "ServerFunction.h"
#include "mysql.h"

int Deal(int *fd, fd_set *ReadFd, Linklist L, ChatLink P)
{
    struct UnKnown Recv;
	int ret, len;
	int Fd;
	char ID[24] = {0};
	memset(&Recv, 0, sizeof(Recv));
	ret = recv(*fd, &Recv, sizeof(Recv), 0); 
	if(-1 == ret)
	{   
		return 1;
	}   
	switch(Recv.Flag)
	{   
		case LOAD:			
			LoadFriList(fd, ReadFd, &Recv);
			break;
		case SIGNIN :
			DealSignin(fd, ReadFd, &Recv);
			break;
		case LOGIN :
			DealLogin(fd, ReadFd, &Recv, L);
			break;
		case CHAT :
			DealChat(fd, ReadFd, &Recv, L, P);
			break;
		case ADDFRIEND:
			DealAddFriend(fd, ReadFd, &Recv);
			break;
		case DELFRIEND:
			DealDelFriend(fd, ReadFd, &Recv);
			break;
		case QUIT:
		default:
			printf("用户退出\n");
			close(*fd);
			FD_CLR(*fd, ReadFd);
			len = ListLocateFromFD(L, *fd, 1);
			ret = ListDelete(L, len, &Fd, ID);
			*fd = -1;
			return 1;
	}
	
	return 0;
}

int DealSignin(int *fd, fd_set *ReadFd, struct UnKnown *Recv)
{
	struct UserInfo* UserInformation;
	UserInformation = (struct UserInfo*)Recv;	
	int IDnum = 0;
	int Flag = 0;
	int ret = 0;

	if (1 == MysqlSelect(UserInformation->ID, UserInformation->passwd, REGIEST, NULL))
	{
		IDnum = 1;
	}
	
	if(1 == IDnum)
	{
		Flag = 8;
		ret = send(*fd, (void *)&Flag, sizeof(Flag), 0);
		if(ret == -1)
		{
			perror("send");
			return 1;
		}
		
		return 1;
	}
	
	MysqlInsert(UserInformation->ID, UserInformation->nickname, UserInformation->passwd);
	
	Flag = 85;
	ret = send(*fd, (void *)&Flag, sizeof(Flag), 0);
	if(ret == -1)
	{
		perror("send");
		return 1;
	}
		
	return 0;
}

int DealLogin(int *fd, fd_set *ReadFd, struct UnKnown *Recv, Linklist L)
{
	struct UserLogin* User_Login = (struct UserLogin*)Recv;
	int flag = 0;
	int ret, status = 0;

	if (1 == MysqlSelect(User_Login->ID, User_Login->passwd, LOGIN, NULL))
	{
		flag = 1;
	}	
	
	if(1 == flag)
	{
		status = SUCCESS;
		ret = send(*fd, (void *)&status, sizeof(status), 0);
		if(ret == -1)
		{
			perror("send");
			return 0;
		}
		ret = ListInsert(L, 1, (*fd), User_Login->ID);
		if(ret != 0)
		{
			printf("ListInsert Error!\n");
		}
	}
	else
	{
		status = 1234;
		ret = send(*fd, (void *)&status, sizeof(status), 0);
		if(ret == -1)
		{
			perror("send");
			return 0;
		}
	}

	return 0;
}

int AddFriend(char *id, char *mainID)
{
	return MysqlSelect(id, mainID, FRIENDLIST, NULL);
}

int DealAddFriend(int *fd, fd_set *ReadFd, struct UnKnown *Recv)
{
	struct UserLogin* User_Login = (struct UserLogin*)Recv;
	int ret = 0;
	int i = 0;
	struct OnlineInfo Info;
	memset(&Info, 0, sizeof(Info));
	Info.Flag = NOUSER;
	Info.Max = 0;
	printf("User_Login->ID = %s\n", User_Login->ID);
	printf("User_Login->passwd = %s\n", User_Login->passwd);
	ret = MysqlSelect(User_Login->passwd, NULL, SHOW, &Info);
	if (ret == 0)
	{
		Info.Flag = NOUSER;
	}
	printf("ret = %d\n", ret);
	for (i = 0; i < ret; i++)
	{
		printf("User_Login->ID = %s,  Info.users[i].ID = %s\n", User_Login->ID, Info.users[i].ID);
		if (!strcmp(User_Login->ID, Info.users[i].ID))
		{
			if (1 == AddFriend(User_Login->ID, User_Login->passwd))
			{
				Info.Flag = ALREADY;
			}
			else
			{				
				MysqlUpdate(User_Login->passwd, User_Login->ID, ADDING);
				Info.Flag = ADDFRIEND;
			}
		}
	}
	strcpy(Info.users[ret].ID, User_Login->ID);
	ret = send(*fd, (void *)&Info, sizeof(Info), 0);
    if(ret == -1)
	{
		perror("send");
		return 1;
	}

	return 0;
}

int DealDelFriend(int *fd, fd_set *ReadFd, struct UnKnown *Recv)
{
	struct UserLogin* User_Login = (struct UserLogin*)Recv;
	int ret = 0;
	struct OnlineInfo Info;
	memset(&Info, 0, sizeof(Info));
	Info.Flag = DELETE;
	Info.Max = 0;
	printf("User_Login->ID = %s\n", User_Login->ID);
	printf("User_Login->passwd = %s\n", User_Login->passwd);
			
	if ((MysqlUpdate(User_Login->passwd, User_Login->ID, DELETE)) == ERROR)
	{
		Info.Flag = DELNOUSER;
	}
	
	ret = send(*fd, (void *)&Info, sizeof(Info), 0);
    if(ret == -1)
	{
		perror("send");
		return 1;
	}

	return 0;
}

int DealChat(int *fd, fd_set *ReadFd, struct UnKnown *Recv, Linklist L, ChatLink P)
{
	struct ChatInfo* tmp = (struct ChatInfo*)Recv;
    int ret, locatefrom, locateto, flag = 0;
	int tofd, fromfd, i;
	char ID[24] = {0};
	char ID1[24] = {0};

	locatefrom = ListLocateFromFD(L, *fd, 0);
	if(locatefrom == -1)
	{
		printf("Error\n");
	}

	ret = GetElem(L, locatefrom, &fromfd, ID1);
	if(ret)
	{
		printf("Error!\n");
	}

	if(strcmp(tmp->ToId, "Group"))
	{
		locateto = ListLocate(L, tmp->ToId);
		
		if(locateto == -1)
		{
			flag = 567;
			ret = send(*fd, (void *)&flag, sizeof(flag), 0);
			if(-1 == ret)
			{
				perror("send");
				return 0;
			}
			return 0;
		}

		ret = GetElem(L, locateto, &tofd, ID);
		
		if(ret)
		{
			printf("Error!\n");
		}

		if(strlen(tmp->Message))
		{
			ret = ChatLinkInsert(P, ChatLinkLength(P) + 1, tmp->MyId, tmp->ToId, tmp->Message);
			if(ret)
			{
				printf("ChatLinkInsert Error\n");
			}
		}
		
		ret = send(tofd, (void *)Recv, sizeof(*Recv), 0);
		if(-1 == ret)
		{
			perror("send");
			return 1;
		}
		else
		{
			printf("send success!\n");
			return 0;
		}
	}
	else if(!strcmp(tmp->ToId, "Group"))
	{
		if(strlen(tmp->Message))
		{
			ret = ChatLinkInsert(P, ChatLinkLength(P) + 1, tmp->MyId, tmp->ToId, tmp->Message);
			if(ret)
			{
				printf("ChatLinkInsert Error\n");
			}
		}
        printf("len = %d\n", ListLength(L));
		for(i = 1; i <= ListLength(L); i++)
		{
			if(i == locatefrom)
			{
				continue;
			}
			memset(ID, 0, sizeof(ID));
			ret = GetElem(L, i, &tofd, ID);
			if(ret)
			{
				printf("Error!\n");
			}
            printf("Myid = %s, tofd = %d\n", tmp->MyId, tofd);
			ret = send(tofd, (void *)Recv, sizeof(*Recv), 0);
			if(-1 == ret)
			{
				perror("send");
				return 1;
			}
		}
		return 0;
	}
	return 1;
}

int LoadFriList(int *fd, fd_set *ReadFd, struct UnKnown *Recv)
{
	struct UserLogin* User_Login = (struct UserLogin*)Recv;
	int ret = 0;
	int i = 0;
	struct OnlineInfo Info;
	memset(&Info, 0, sizeof(Info));
	Info.Flag = LOAD;
	Info.Max = 0;
	printf("<<< %s\n", User_Login->ID);
	ret = MysqlSelect(User_Login->ID, NULL, LOAD, &Info);
	printf(">>> %s\n", Info.users[0].ID);
	ret = send(*fd, (void *)&Info, sizeof(Info), 0);
    if(ret == -1)
	{
		perror("send");
		return 1;
	}

	return 0;
}
