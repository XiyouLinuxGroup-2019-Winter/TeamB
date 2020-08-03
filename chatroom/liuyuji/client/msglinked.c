/*************************************************************************
	> File Name: msglinked.c
	> Author: 
	> Mail: 
	> Created Time: 2020年08月03日 星期一 11时02分43秒
 ************************************************************************/

#include"client.h"
int addnode(char *send_id,char *recv_id,char *msg)
{
    Node *operate=(Node*)malloc(sizeof(Node));
    memset(operate,0,sizeof(Node));
    strcpy(operate->send_id,send_id);
    strcpy(operate->recv_id,recv_id);
    strcpy(operate->msg,msg);
    operate->next=NULL;
    P_LOCK;
    P_UNLOCK;
    LOCK;
    if(Msg.num==0){
        Msg.head=operate;
        Msg.tail=operate;
        Msg.num++;
    }
    else{
        Node *record=Msg.tail;
        record->next=operate;
        Msg.num++;
    }
    UNLOCK;
    printf("addnode over\n");
}
int delnode()
{
    LOCK;
    Node *operate=Msg.head;
    Node *record=operate->next;
    free(operate);
    Msg.num--;
    Msg.head=record;
    if(Msg.num==0){
        Msg.tail=NULL;
    }
    UNLOCK;
}
int printnode()
{
    Node *operate;
    LOCK;
    operate=Msg.head;
    for(int i=0;i<Msg.num;i++){
        P_LOCK;
        printf("\t\t\t%s--->%s:%s\n",operate->send_id,operate->recv_id,operate->msg);
        P_UNLOCK;
        operate=operate->next;
    }
    UNLOCK;
}

