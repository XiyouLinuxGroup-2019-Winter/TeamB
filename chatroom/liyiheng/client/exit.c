#include"client.h"
void drop_out(int sockfd)
{
  recv_package send;
  printf("请输入要退出的账号\n");
  scanf("%s",send.nikename);
    //写进服务器
  if(-1 == write(sockfd,&send,sizeof(send)))
  {
    perror("write1");
    exit(1);
  }
}
 


