/*************************************************************************
	> File Name: pc_queue.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月14日 星期四 21时22分23秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct node{
    int date;
    struct node *next;
}Node;
typedef struct queue{
    Node *head;
    Node *tail;
    int num;
    int len;
}Queue;
Queue pc;
int full(Queue *p)
{
    if(p->len==p->num){
        return 1;
    }
    else{
        return 0;
    }
}
int empty(Queue *p)
{
    if(p->head==NULL){
        return 1;
    }
    else{
        return 0;
    }
}
void create(Queue *p)
{
    p->num=10;
    p->head=NULL;
    p->tail=NULL;
    p->len=0;
}
int insert(Queue *p)
{
    Node *operate,*record;
    operate=(Node *)malloc(sizeof(Node));
    if(p->head==NULL){
        p->head=operate;
    }
    else{
        record=p->tail;
        record->next=operate;
    }
    operate->date=0;
    p->tail=operate;
    p->len++;
    return 0;
}
void rm(Queue *p)
{
    Node *operate=p->head;
    Node *record=operate->next;
    free(operate);
    p->head=record;
    p->len--;
}
void del(Queue *p)
{
    Node *operate,*record;
    operate=p->head;
    for(int i=0;i<p->len;i++){
        record=operate->next;
        free(operate);
        operate=record;
    }
}
