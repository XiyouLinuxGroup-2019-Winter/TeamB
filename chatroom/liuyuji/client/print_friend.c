/*************************************************************************
	> File Name: print_friend.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月30日 星期四 10时47分18秒
 ************************************************************************/

#include"client.h"
int print_friend()
{
    while(1){
        printf("1.查看好友列表\n");
        printf("2.添加好友\n");
        printf("3.删除好友\n");
        printf("4.拉黑好友\n");
        printf("5.聊天\n");
        printf("6.返回\n");
        int chose;
        scanf("%d",&chose);
        switch(chose){
            /*case 1:
            
            break;*/
            case 2:
            addfriend();
            break;
            /*case 3:
            break;
            case 1:
            break;
            case 1:
            break;
            case 1:
            break;*/
            case 6:
            return 0;
            break;
        }
    }
}
