#include "main.h"
#include "ClientFunction.h"
#include "signal.h"

int i = 0;
char MyID[24];
char ToOther[24];
FILE *fp;

int main(int argc, char *argv[])
{	
	signal(SIGINT, SIG_IGN);
	int sockfd;
	struct sockaddr_in sever_addr;
	struct UserInfo Info;
	int cmd = 0;
	Linklist OtherUserInfo;
	ChatLink ChatInformation;

	if(2 != argc)
	{
		printf("Usge:  ./Client <IP>!\n");
		return -1;
	}

	ListInit(&OtherUserInfo);
	ChatLinkInit(&ChatInformation);

	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	
	memset(&sever_addr, 0, sizeof(struct sockaddr_in));
	sever_addr.sin_family = AF_INET;
	sever_addr.sin_port = htons(PORT);
	sever_addr.sin_addr.s_addr = inet_addr(argv[1]);

	connect(sockfd, (struct sockaddr *)&sever_addr, sizeof(sever_addr)); 
	memset(&Info, 0, sizeof(Info));
	
	while(1)
	{
		LOGINInterface();
		while(1)
		{
			scanf("%d", &cmd);
			if (cmd < 1 || cmd > 3)
			{
				printf("输入错误，请重新输入！\n");
				continue;
			}
			break;
		}
		switch(cmd)
		{
			case 1:
				Login(&sockfd, OtherUserInfo, ChatInformation);
				break;
			case 2:
				Register(&sockfd);
				break;
			default:
				return 0;
		}
	}
	
	return 0;
}
