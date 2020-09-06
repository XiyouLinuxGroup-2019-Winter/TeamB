#include "main.h"
#include "ClientFunction.h"
#include "mysql.h"

extern char MyID[24];
extern char ToOther[24];
extern FILE *fp;
extern int i;
char FriendList[100][24];
char friend_nick[20][24];
int  max_friend;
int LoadFlag = 0;

void LOGINInterface()
{
    system("clear");
	printf("\t\t\t\t\t\t+++++++++++++++++++++++++++++++++\n");
	printf("\t\t\t\t\t\t++                             ++\n");
	printf("\t\t\t\t\t\t++          1.登陆             ++\n");
	printf("\t\t\t\t\t\t++          2.注册	           ++\n");
	printf("\t\t\t\t\t\t++          3.退出	           ++\n");
	printf("\t\t\t\t\t\t++                             ++\n");
	printf("\t\t\t\t\t\t+++++++++++++++++++++++++++++++++\n");
	printf("\t\t\t\t\t\t请选择: ");

}

void ChatInterface()
{
    system("clear");
	printf("\t\t\t\t\t\t\t\t1.私聊\n");
	printf("\t\t\t\t\t\t\t\t2.群聊\n");	
	printf("\t\t\t\t\t\t\t\t3.添加好友\n");
	printf("\t\t\t\t\t\t\t\t4.删除好友\n");
	printf("\t\t\t\t\t\t\t\t5.退出\n");
	printf("\t\t\t\t\t\t请选择: ");
}

int addFriend(int *sockfd)
{
    int ret = 0;
    int cmd = 0;
	
	struct UserLogin tmp;
	memset(&tmp, 0, sizeof(struct UserLogin));
	tmp.Flag = ADDFRIEND;
	printf("please input the ID you want to add: ");	
    scanf("%s", tmp.ID);
	if (!strcmp(MyID, tmp.ID))
	{
		printf("不能添加自己！\n");
		sleep(1);
		return 1;
	}
	strcpy(tmp.passwd, MyID);
	if ((ret = send(*sockfd, (void *)&tmp, sizeof(tmp), 0)) == -1)
    {
        perror("send");
        return 1;
    }
    else
    {
        while(1)
        {
            sleep(5);
            printf("输入 1 退出...:  ");
            scanf("%d", &cmd);
            if (cmd == 1)
            {
                return 0;
            }
        }
    }
	
    return 0;
}

int Register(int *sockfd)
{
	char ID[24];
	char nickname[24];
	char passwd[24];
	char confirmpasswd[24];
	char question[48];
	char answer[48];
	int ret, Flag = 0, i;
	struct UserInfo NewUserInfo;
	char cmd[24];
	memset(&NewUserInfo, 0, sizeof(NewUserInfo));
	while(1)
	{
		Flag = 0;
		memset(ID, 0, sizeof(ID));
		memset(nickname, 0, sizeof(nickname));
		memset(passwd, 0, sizeof(passwd));
		memset(confirmpasswd, 0, sizeof(confirmpasswd));
		memset(question, 0, sizeof(question));
		memset(answer, 0, sizeof(answer));
		NewUserInfo.Flag = SIGNIN;
		printf("\n\n\n");
		printf("\t\t\t\t\t\t账号:");
		scanf("%s", ID);
		printf("\n");
		sprintf(NewUserInfo.ID, "%s", ID);

		printf("\t\t\t\t\t\t昵称:");
		scanf("%s", nickname);
		printf("\n");
		sprintf(NewUserInfo.nickname, "%s", nickname);

		printf("\t\t\t\t\t\t密码:");
		system("stty -echo");
		scanf("%s", passwd);
		system("stty echo");
		for(i = 0; i < strlen(passwd); i++)
		{
			printf("*");
		}	
		printf("\n");
		printf("\t\t\t\t\t\t确认密码:");
		system("stty -echo");
		scanf("%s", confirmpasswd);
		system("stty echo");
		for(i = 0; i < strlen(confirmpasswd); i++)
		{
			printf("*");
		}
		printf("\n");
		while(strcmp(confirmpasswd, passwd))
		{
			memset(confirmpasswd, 0, sizeof(confirmpasswd));
			printf("\t\t\t\t\t\t请重新输入密码:");
			system("stty -echo");
			scanf("%s", confirmpasswd);
			system("stty echo");
			for(i = 0; i < strlen(confirmpasswd); i++)
			{
				printf("*");
			}
			printf("\n");
		}
		sprintf(NewUserInfo.passwd, "%s", passwd);
		
		ret = send(*sockfd, (void *)&NewUserInfo, sizeof(NewUserInfo), 0);
		if(-1 == ret)
		{
			perror("send");
			return 1;
		}

		ret = recv(*sockfd, (void *)&Flag, sizeof(Flag), 0);
		if(-1 == ret)
		{
			perror("recv");
			return 1;
		}

		if(85 == Flag)
		{
			system("clear");	
			printf("\n\n\n\n\n\n\n\n\n");
			printf("\t\t\t\t\t\t注册成功！\n");
			printf("\t\t\t\t\t\t按Enter键继续...\n");
			getchar();
			getchar();
			return 0;
		}
		else
		{
			system("clear");	
			printf("\n\n\n\n\n\n\n\n\n");
			if(8 == Flag)
			{
				printf("\t\t\t\t\t\t账号重复,注册失败！\n");
			}
			else
			{
				printf("\t\t\t\t\t\t注册失败！\n");
			}
			printf("\t\t\t\t\t\t输入'q'退出注册界面,输入'r'重新注册:");
			scanf("%s", cmd);
			printf("\n");
			while(strlen(cmd) != 1)
			{
				memset(cmd, 0, sizeof(cmd));
				printf("\t\t\t\t\t\t输入'q'退出注册界面,输入'r'重新注册:");
				scanf("%s", cmd);
				printf("\n");
			}
			if(cmd[0] == 'r')
			{
				continue;
			}
			else if (cmd[0] == 'q')
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
	}
	return 1;
}

int Load(int *sockfd)
{
	struct UserLogin User_Login;
	memset(&User_Login, 0, sizeof(User_Login));
	User_Login.Flag = LOAD;
	strcpy(User_Login.ID, MyID);
	int ret = send(*sockfd, (void *)&User_Login, sizeof(User_Login), 0);
	if(-1 == ret)
	{
		perror("send");
		return 1;
	}

	return 0;
}

int Login(int *sockfd, Linklist L, ChatLink P)
{
	int ret, Flag = 0, i;
	char ID[24] = {0};
	char passwd[24] = {0};
	struct UserLogin User_Login;
	memset(&User_Login, 0, sizeof(User_Login));
	User_Login.Flag = LOGIN;
	ChatLink tmp = (ChatLink)malloc(sizeof(ChatLinklist));
	memset(tmp, 0, sizeof(ChatLinklist));
	while(1)
	{
		system("clear");
		printf("\n\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t\t\t账号:");
		scanf("%s", ID);
		printf("\n");
		printf("\t\t\t\t\t\t密码:");
		system("stty -echo");
		scanf("%s", passwd);
		system("stty echo");
		for(i = 0; i < strlen(passwd); i++)
		{
			printf("*");
		}
		printf("\n");
		printf("\n");
		sprintf(User_Login.ID, "%s", ID);
		sprintf(User_Login.passwd, "%s", passwd);

		ret = send(*sockfd, (void *)&User_Login, sizeof(User_Login), 0);
		if(-1 == ret)
		{
			perror("send");
			return 1;
		}
		
		ret = recv(*sockfd, (void *)&Flag, sizeof(Flag), 0);
		if(-1 == ret)
		{
			perror("recv");
			return 1;
		}
		
		switch(Flag)
		{
			case SUCCESS:
				printf("登陆成功！\n");
				sprintf(MyID, "%s", ID);	
				if (LoadFlag == 0)
				{
					LoadFlag = 1;
					Load(sockfd);
				}
				sleep(2);
                ret = MainChat(sockfd, L, P);
				if(10 == ret)
				{
					return 10;
				}
				else if(0 != ret)
				{
					printf("MainChat Error Occured!\n");
				}
				return SUCCESS;
			case 1234:
				system("clear");
				printf("\n\n\n\n\n\n\n\n\n");
				printf("\t\t\t\t\t\t用户名或者密码错误!\n");
				printf("\t\t\t\t\t\t按Enter键继续...\n");
				getchar();
				getchar();
				return 1234;
			case 3456:
				system("clear");
				printf("\n\n\n\n\n\n\n\n\n");
				printf("\t\t\t\t\t\t服务器错误!\n");
				printf("\t\t\t\t\t\t按Enter键继续...\n");
				getchar();
				getchar();
					return 3456;
			default:
				printf("unknown\n");
				printf("Error\n");
					break;
		}
		
	}
	return 1;
} 

int MainChat(int *sockfd, Linklist L, ChatLink P)
{
	int ret;
	int Flag;
	pthread_t tid;
	int cmd; 
	struct RecvMessage RecvFromSever;
	memset(&RecvFromSever, 0, sizeof(RecvFromSever));
	RecvFromSever.sockfd = (*sockfd);
	RecvFromSever.L = L;
	RecvFromSever.P = P;
	ret = pthread_create(&tid, NULL, FunctionRecv, (void *)&RecvFromSever);
	if(0 != ret)
	{
		perror("pthread_create");
	}
	while(1)
	{
		ChatInterface();
		scanf("%d", &cmd);
		switch(cmd)
		{			
			case 1:
				printf("私聊\n");
				ret = whisper(sockfd, L, P);
                if(ret)
                {
                    printf("Error!\n");
                }
				break;
			case 2:
				printf("群聊\n");
				ret = GroupChat(sockfd, L, P);
				if(ret)
				{
					printf("Error!\n");
				}
				break;				
			case 3:
				printf("添加好友\n");
				ret = addFriend(sockfd);
				if(ret)
				{
					printf("Error!\n");
				}
				break;
			case 4:
				printf("删除好友\n");
				ret = delFriend(sockfd);
				if(ret)
				{
					printf("Error!\n");
				}
				break;			
			case 5:
				printf("退出\n");
				Flag = QUIT;
				ret = send(*sockfd, (void *)&Flag, sizeof(Flag), 0);
				if(ret == -1)
				{
					perror("send");
				}
				close(*sockfd);
				exit(0);
			default :
				printf("Error\n");
				break;
		}
	}
	return 0;
}

int isFriend(char *ID)
{
	char id[32] = {0};
	printf("\n\t\t\t\t\t\t想私聊的用户ID: ");
	scanf("%s", id);	
	if (!strcmp(MyID, id))
	{
		printf("不能和自己私聊！\n");
		return 0;
	}
	strcpy(ID, id);
	int i = 0;
	while(strlen(FriendList[i]) != 0)
	{
		if (!strcmp(id, FriendList[i]))
			return 1;
		i++;
	}

	return 0;
}

int whisper(int *sockfd, Linklist L, ChatLink P)
{
	struct ChatInfo chat;
	memset(&chat, 0, sizeof(chat));
	
	char id[24] = {0};
	char message[512] = {0};
	char to[24] = {0};
	char from[24] = {0};
	char mes[512] = {0};
	int ret, i;	

	if (isFriend(id) != 1)
	{
		printf("此用户还不是你的好友！\n");
		sleep(1);
		return 0;
	}
	
	if(!strcmp(id, "q"))
	{
		return 0;
	}	
	
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t%s\n", id);
	sprintf(ToOther, "%s", id);
	for(i = 1; i <= ChatLinkLength(P); i++)
	{
		memset(from, 0, sizeof(from));
		memset(to, 0, sizeof(to));
		memset(mes, 0, sizeof(mes));
		ret = GetChatLink(P, i, from, to, mes);
		if(ret)
		{
			printf("Error\n");
		}
		if(!strcmp(from, ToOther) && strcmp(to, "Group"))
		{
			printf("\t\t\t\t\t%s:%s\n",from, mes);
		}
	}
    strcpy(chat.ToId, id);
	printf("输入 'quit' 离开\n");
	while(1)
	{	
		//sleep(2);
		memset(&chat, 0, sizeof(chat));
		chat.Flag = CHAT;
		sprintf(chat.MyId, "%s", MyID);
		sprintf(chat.ToId, "%s", id);
		sprintf(ToOther, "%s", id);
		memset(message, 0, sizeof(message));
		fgets(message, 512, stdin);
		message[strlen(message)-1] = '\0';
		if(!strcmp(message, "quit"))
		{
			memset(ToOther, 0, sizeof(ToOther));
			break;
		}
		sprintf(chat.Message, "%s", message);
		ret = send(*sockfd, (void *)&chat, sizeof(chat), 0);
		if(-1 == ret)
		{
			perror("send");
			return 1;
		}
		if(strlen(message) != 0)
		{
			ret = ChatLinkInsert(P, ChatLinkLength(P) + 1, MyID, ToOther, message);
			if(ret)
			{
				printf("ChatLinkInsert Error\n");
			}
		}
	}

	return 1;
}

int GroupChat(int *sockfd, Linklist L, ChatLink P)
{
	struct ChatInfo chat;
	char message[512] = {0};
	char to[24] = {0};
	char from[24] = {0};
	char mes[512] = {0};
	int ret, i;
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t群聊\n");
	sprintf(ToOther, "Group");
	for(i = 1; i <= ChatLinkLength(P); i++)
	{
		memset(from, 0, sizeof(from));
		memset(to, 0, sizeof(to));
		memset(mes, 0, sizeof(mes));
		ret = GetChatLink(P, i, from, to, mes);
		if(ret)
		{
			printf("Error\n");
		}
		if(!strcmp(to, "Group"))
		{
			printf("\t\t\t\t\t%s:%s\n",from, mes);
		}
	}
	while(1)
	{
		memset(&chat, 0, sizeof(chat));
		chat.Flag = CHAT;
		sprintf(chat.ToId, "Group");
		sprintf(chat.MyId, MyID);
		sprintf(ToOther, "Group");
		memset(message, 0, sizeof(message));
		fgets(message, sizeof(message), stdin);
		message[strlen(message)-1] = '\0';
		if(!strcmp(message, "quit"))
		{
			memset(ToOther, 0, sizeof(ToOther));
			return 0;
		}
		sprintf(chat.Message, "%s", message);
		
		ret = send(*sockfd, (void *)&chat, sizeof(chat), 0);
		if(-1 == ret)
		{
			perror("send");
			return 1;
		}
		if(strlen(message) != 0)
		{
			ret = ChatLinkInsert(P, ChatLinkLength(P) + 1, MyID, ToOther, message);
			if(ret)
			{
				printf("ChatLinkInsert Error\n");
			}
		}		
	}

	return 1;
}

int delFriend(int *sockfd)
{
	int ret = 0;
    int cmd = 0;
	
	struct UserLogin tmp;
	memset(&tmp, 0, sizeof(struct UserLogin));
	tmp.Flag = DELFRIEND;
	printf("请输入要删除的好友的ID号: ");	
    scanf("%s", tmp.ID);
	strcpy(tmp.passwd, MyID);
	if ((ret = send(*sockfd, (void *)&tmp, sizeof(tmp), 0)) == -1)
    {
        perror("send");
        return 1;
    }
    else
    {
        while(1)
        {
            sleep(5);
            printf("输入 1 退出...:  ");
            scanf("%d", &cmd);
            if (cmd == 1)
            {
                return 0;
            }
        }
    }
	
    return 0;
}

void clearList()
{
	int i = 0;
	while(strlen(FriendList[i]) != 0)
	{
		memset(FriendList[i], 0, sizeof(FriendList[i]));
		i++;
	}
}

void *FunctionRecv(void *arg)
{
	int ret;
	struct RecvMessage* tmp = (struct RecvMessage*)arg;
	struct UnKnown Recved;
	int i = 0;
	struct OnlineInfo* FriendInfo;
	
	while(1)
	{	
		memset(&Recved, 0, sizeof(Recved));
		ret = recv(tmp->sockfd, (void *)&Recved, sizeof(Recved), 0);
		if(-1 == ret)
		{
			perror("recv");
			continue;
		}
		switch(Recved.Flag)
		{
			case CHAT:
				ret = DealChat(tmp->L, &Recved, tmp->P);
				if(ret)
				{
					printf("Error happened!\n");
				}				
				break;	
            case ADDFRIEND:
			case LOAD:
				FriendInfo = (struct OnlineInfo *)&Recved;
				clearList();
				for (i = 0; strlen(FriendInfo->users[i].ID) != 0; i++)
				{
					strcpy(FriendList[i], FriendInfo->users[i].ID);
				}
                printf("添加成功!\n");                
                break;      
			case NOUSER:
				printf("此用户ID不存在!\n");
				break; 
			case ALREADY:
				printf("该用户已经是您的好友！\n");
				break;
			case DELETE:
				clearList();
				FriendInfo = (struct OnlineInfo*)&Recved;
				for (i = 0; strlen(FriendInfo->users[i].ID) != 0; i++)
				{
					strcpy(FriendList[i], FriendInfo->users[i].ID);
				}
				printf("删除成功！\n");
				break;
			case DELNOUSER:
				printf("删除失败！此账户不是你的好友！\n");
				break;
			case NOTFRIEND:
				printf("此账户还不是你的好友！\n");
				break;
			case 567:
				printf("对方不在线!\n");
				break;
			default:
				break;
		}
	}
	return (void *)0;
}

int DealLoad(struct UnKnown *Recved)
{
	
}


int DealChat(Linklist L, struct UnKnown *Recved, ChatLink P)
{
	struct ChatInfo* tmp = (struct ChatInfo*)Recved; 
	int ret;
	if(strlen(tmp->Message) == 0)
	{
        printf("空消息!\n");
		return 0;
	}
	ret = ChatLinkInsert(P, ChatLinkLength(P) + 1, tmp->MyId, tmp->ToId, tmp->Message);
	if(ret)
	{
		printf("Error in ChatLinkInsert\n");
	}

	if((!strcmp(tmp->MyId, ToOther) && strcmp(tmp->ToId, "Group")))
	{	
		printf("\t\t\t\t\t%s 说 %s\n", tmp->MyId, tmp->Message);
	}
	else if((!strcmp(tmp->ToId, "Group")) && !strcmp(tmp->ToId, ToOther))
	{
		printf("\t\t\t\t\t%s 说 %s\n", tmp->MyId, tmp->Message);
	}
	else
	{
		if(!strcmp(tmp->ToId, "Group"))
		{
			printf("\n\t\t\t\t\t\t收到群聊的消息\n");
			fflush(stdin);
		}
		else
		{
			printf("\n\t\t\t\t\t\t收到来自好友 %s 的消息\n", tmp->MyId);
			fflush(stdin);
		}
	}	
	
	return 0;
}
