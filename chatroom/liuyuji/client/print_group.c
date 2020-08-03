/*************************************************************************
	> File Name: print_group.c
	> Author: 
	> Mail: 
	> Created Time: 2020年08月03日 星期一 21时01分35秒
 ************************************************************************/

#include"client.h"
int print_group()
{
    while(1){ 
        P_LOCK;
        printf("1.查看群列表\n");
        printf("2.创建群\n");
        printf("3.添加群\n");
        printf("4.退出群\n");
        printf("5.设置管理员\n");
        printf("6.踢人\n");
        printf("7.解散群\n");
        printf("8.群聊\n");
        printf("0.返回\n");
        P_UNLOCK;
        int chose;
        scanf("%d",&chose);
        switch(chose){
            case 1:
            grouplist();
            break;
            case 2:
            creategroup();
            break;
            /*case 3:
            print_file();
            break;
            case 4:
            print_chatmsg();
            break;*/
            case 0:
            return 0;
            break;
        }
    }
}

