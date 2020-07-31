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
        printf("1.好友管理\n");
        printf("2.群管理\n");
        printf("3.发送文件\n");
        printf("4.聊天记录\n");
        printf("5.消息盒子\n");
        printf("0.注销\n");
        printf("请输入您的选择\n");
        scanf("%d",&chose);
        switch(chose){
            case 1:
            print_friend();
            break;
            /*case 2:
            print_group();
            break;
            case 3:
            print_file();
            break;
            case 4:
            print_chatmsg();
            break;
            case 5:
            print_box();
            break;*/
            case 0:
            return 0;
            break;
        }
    }
}

