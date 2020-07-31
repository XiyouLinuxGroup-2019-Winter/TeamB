#include"client.h"

void regist(int sockfd)
{   
    recv_package send;
    char buffer[1024]={0};
    printf("请输入昵称\n");
    scanf("%s",send.nikename);
    printf("请输入密码\n");
    scanf("%s",send.password);
    printf("请确认密码\n");
    scanf("%s",send.password1);

    if(write(sockfd,&send,sizeof(send)) == -1)
    {
        perror("write error");
        exit(2);
    }

    if(read(sockfd,&send,sizeof(send)) == -1)
    {
        perror("read error");
        exit(4);
    }

    if(send.num != 0)
    {
        printf("两次密码不一致，请重新输入\n");
    }

    else
    {
        printf("注册成功\n");
    }

}

