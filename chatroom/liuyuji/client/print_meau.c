/*************************************************************************
	> File Name: print_meau.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月30日 星期四 10时37分19秒
 ************************************************************************/

#include"client.h"
int print_meau()
{
    int chose;
    while(1){
        P_LOCK;
        printf("1.好友管理\n");
        printf("2.群管理\n");
        printf("3.发送文件\n");
        printf("4.聊天记录\n");
        printf("0.注销\n");
        printf("请输入您的选择\n");
        P_UNLOCK;
        S_LOCK;
        scanf("%d",&chose);
        S_UNLOCK;
        switch(chose){
            case 1:
            print_friend();
            break;
            case 2:
            print_group();
            break;/*
            case 3:
            print_file();
            break;
            case 4:
            print_chatmsg();
            break;*/
            case 0:
            exit_flag=1;
            char data[11];
            sprintf(data,"%s\n",user_id);
            send_pack(connfd,OVER,strlen(data),data);
            return 0;
            break;
        }
    }
}