#include"client.h"


int memu_1(int sockfd)
{
    recv_package send;
    while(1)
    {
        printf("\t\t1:私聊\n");
        printf("\t\t2:群聊\n");
        printf("\t\t3:显示在线成员\n");
        printf("\t\t4:文件传输\n");
        printf("\t\t5:退出聊天界面\n");
        scanf("%d",&send.seg);
        if(write(sockfd,&send,sizeof(send)) == -1)
        {
            perror("write2");
            exit(5);
                    
        }
        switch(send.seg)
        {
            case 1:
            private_chat(sockfd);
            break;
            case 2:
            group_chat(sockfd);  //群聊
            break;
            case 3:
            show_state(sockfd);
            break;  //显示在线成员
            case 4:
            file_transfer(sockfd);
            file_transfer(sockfd);
            case 5:
            printf("退出聊天界面\n");
            return 0;
    
        }
 
    }
   return 0;

}



//菜单主界面
int memu(int sockfd) 
{
    recv_package send;
    while(1)
    {
        printf("1.登录账号\n");
        printf("2.注册账号\n");
        printf("3:退出账号\n");
        scanf("%d",&send.seg);
        if(write(sockfd,&send,sizeof(send)) == -1)
        {
            perror("write3");
            exit(5);
        }


        switch(send.seg)
        {
            case 1:
            login(sockfd);
            break;

            case 2:
            regist(sockfd);
            break;

            case 3:
            drop_out(sockfd);
            break   
            printf("退出账号\n");
            return 0;
        }

    }        
    return 0;
}

