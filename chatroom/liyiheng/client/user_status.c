#include"client.h"

void *net_thread_1(void *fd)
{
    recv_package send;
    pthread_detach(pthread_self());
    int sockfd = *((int)fd);

    while(1)
    {
        if(read(sockfd,&send,sizeof(send)) == -1)
        {
            perror("read");
            exit(5);
        }

        switch(send.num)
        {
            case 11:printf("用户在线\n");
            break;
            case 12:printf("用户不在线\n");
            break;
            case 13:printf("用户不存在\n");
            break;
            case 14:printf("输出错误\n");
            break;
            case 15:printf("(私聊)%s : %s\n",send.nikename1,send.text);
            break;//发送给本机客户端
            case 16:printf("(私聊)%s : %s\n",send.nikename1,send.text);
            break;//发送给要私聊客户
            case 17:printf("%s\n",send.nikename);
            break;//在线成员
            case 18:printf("(群聊)%s : %s\n"send.nikename,send.text);
            break;//给在线成员发送群聊消息

        }
    }
}
