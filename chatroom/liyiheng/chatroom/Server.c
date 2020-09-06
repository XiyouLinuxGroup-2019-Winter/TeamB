#include "main.h"
#include "ServerFunction.h"
#include "mysql.h"

int main()
{
	int sockfd, MaxFd, ret, fd[64] = {0}, i = 0, j, k = 0;
	socklen_t length;
	int opt = 1;
	struct sockaddr_in sever_addr, client_addr;
	fd_set ReadFd, TmpFd;
	Linklist OnlineUser;
	ChatLink ChatInformation;

	ListInit(&OnlineUser);
	ChatLinkInit(&ChatInformation);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd)
	{
		perror("socket");
		exit(1);
	}		

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	memset(&sever_addr, 0, sizeof(sever_addr));
	sever_addr.sin_family = AF_INET;
	sever_addr.sin_port = htons(PORT);
	sever_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	ret = bind(sockfd, (struct sockaddr *)&sever_addr, sizeof(sever_addr));
	if (-1 == ret)
	{
		perror("bind");
		exit(1);
	}
	
	ret = listen(sockfd, 15);
	if (-1 == ret)
	{
		perror("listen");
		exit(1);
	}
	
	FD_ZERO(&ReadFd);
	FD_ZERO(&TmpFd);
	FD_SET(sockfd, &ReadFd);
	MaxFd = sockfd;

	MysqlCreateTable();
	
	printf("Waiting...\n");

	while(1)
	{
		TmpFd = ReadFd;
		ret = select(MaxFd + 1, &TmpFd, NULL, NULL, NULL);
		if(-1 == ret)
		{
			perror("select");
			exit(1);
		}
		
		if (FD_ISSET(sockfd, &TmpFd))
		{
			length = sizeof(client_addr);
			fd[i] = accept(sockfd, (struct sockaddr *)&client_addr, &length);
			if(fd[i] < 0)
			{
				perror("accept");
				exit(1);
			}
			FD_SET(fd[i], &ReadFd);
			MaxFd = ((MaxFd > fd[i])? MaxFd :fd[i]);
			i++;
		}
		else
		{
			for(j = 0; j < i; j++)
			{
				if(fd[j] == -1)
				{
					continue;
				}
				if(FD_ISSET(fd[j], &TmpFd))
				{
					ret = Deal(&fd[j], &ReadFd, OnlineUser, ChatInformation);
					if(1 == ret)
					{
						break;
					}
					k++;
					break;
				}
			}
		}
	}

	return 0;
}
