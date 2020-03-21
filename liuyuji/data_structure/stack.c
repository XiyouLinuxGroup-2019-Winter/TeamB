/*************************************************************************
	> File Name: queue.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月21日 星期六 20时58分58秒
 ************************************************************************/
//队列
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
}Queue;
int main()
{
    printf("请输入队列长度\n");
    int len;
    scanf("%d",&len);
    Queue q;
    create(len,&q);
    printf("插入队列\n");
    int n;
    while((full(&q))==0){
        scanf("%d",%a);
        insert(p,n);
        printf("继续？\n");
        int temp;
        scanf("%d",&temp);
        if(temp==0){
            break;
        }
    }

}
void create(int n,Queue *p)
{
    Node *operate,*record;
    p->num=n;
    operate=record=NULL;
    for(int i=0;i<n;i++){
        operate=(Node *)malloc(sizeof(Node));
        if(i==0){
            p->head=operate;
        }
        else{
            record->next=operate;
        }
        operate->date=0;
        operate->next=NULL;
        record=operate;
    }
}
void insert(Queue *p,int n)
{
    Node *operate,*record;
    if(p->tail==NULL){
        operate=p->head;
    }
    else{
        record=p->tail;
        operate=record->next;
    }
    operate->date=n;
}
void remove(Queue *p)
{

}
void find(Queue *p,int n)
{
    
}
void del(Queue *p)
{
    
}
