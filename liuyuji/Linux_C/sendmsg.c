/*************************************************************************
	> File Name: sendmsg.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月15日 星期三 20时35分46秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
int main()
{
    struct mymsgbuf{
        long msgtype;
        char date[100];
    }mess;
    mess.msgtype=3;
    strcpy(mess.date,"Hallo IPC");
    key_t msgkey=ftok(".",1);
    int mid=msgget(msgkey,IPC_CREAT | 0660);
    msgsnd(mid,&mess,100,0);
    exit(0);
}
