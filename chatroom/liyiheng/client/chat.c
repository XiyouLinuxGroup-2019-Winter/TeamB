#include"client.h"
void group_chat(int sockfd)
{  
    recv_package send;
    printf("自己的昵称\n");
    scanf("%s",send.nikename);
    printf("请输入要群聊的内容\n");
    scanf("%s",send.text);
    printf("nnn\n");
    //写进服务器
    if(-1 == write(sockfd,&send,sizeof(send)))
    {
      perror("write0");
       exit(2);
    }
}
 

void private_chat(int sockfd)
{  
     recv_package send;
     printf("请输入要私聊的用户名\n");
     scanf("%s",send.nikename);
     printf("请输入要私聊的内容\n");
     scanf("%s",send.text);
     printf("请输入自己的用户名\n");
     scanf("%s",send.nikename1); 
     //写进服务器
    if(write(sockfd,&send,sizeof(send)) == -1)
    {
        perror("write0");
        exit(2);
    }
}
    

