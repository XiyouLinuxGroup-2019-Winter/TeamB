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
Node *mark=NULL;
int full(Queue *p)
{
    Node *operate;
    operate=p->tail;
    if(operate==NULL){
        return 0;
    }
    if(operate->next==NULL){
        return 1;
    }
    else{
        return 0;
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
            mark=operate;
        }
        else{
            record->next=operate;
        }
        operate->date=0;
        operate->next=NULL;
        record=operate;
    }
    p->tail=NULL;
}
int insert(Queue *p,int n)
{
    if(full(p)==1){
        return 0;
    }
    Node *operate,*record;
    if(p->tail==NULL){
        operate=p->head;
    }
    else{
        record=p->tail;
        operate=record->next;
    }
    operate->date=n;
    p->tail=operate;
}
void rm(Queue *p)
{
    Node *operate=p->head;
    Node *record=operate->next;
    free(operate);
    p->head=record;
}
void look(Queue *p)
{
    Node *operate=p->head;
    printf("%d\n",operate->date);
}
void del(Queue *p)
{
    Node *operate,*record;
    operate=mark;
    for(int i=0;i<p->num;i++){
        record=operate->next;
        free(operate);
        operate=record;
    }
}
int main()
{
    printf("请输入队列长度\n");
    int len;
    scanf("%d",&len);
    Queue q;
    create(len,&q);
    while(1){
        printf("1.入队\n2.出队\n3.查看队头\n4.清空\n");
        int chose,a;
        scanf("%d",&chose);
        switch(chose){
            case 1:
                while((full(&q))==0){
                    scanf("%d",&a);
                    insert(&q,a);
                    printf("继续？\n");
                    int temp;
                    scanf("%d",&temp);
                    if(temp==0){
                        break;
                    }
                }
                break;
            case 2:
                rm(&q);
                break;
            case 3:
                look(&q);
                break;
            case 4:
                del(&q);
                exit(0);
        }
    }
}
