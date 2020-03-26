/*************************************************************************
	> File Name: stack.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月23日 星期一 16时40分59秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node {
    int date;
    struct node *next;
}Node;
typedef struct stack {
    int num;
    Node *head;
    Node *tail;
}Stack;
void insert(Stack *p,int n)
{
    Node *operate=(Node *)malloc(sizeof(Node));
    Node *record=NULL;
    if(p->head==NULL){
        p->head=operate;
        p->tail=operate;
        operate->next=NULL;
    }
    else{
        record=p->head;
        operate->next=record;
        p->head=operate;
    }
    operate->date=n;
    p->num++;
}
int rm(Stack *p)
{
    Node *operate,*record;
    operate=p->head;
    record=operate->next;
    free(operate);
    p->head=record;
    p->num--;
    return 1;
}
void look(Stack *p)
{
    Node *operate;
    operate=p->head;
    printf("%d\n",operate->date);
}
void del(Stack *p)
{
    Node *operate,*record;
    operate=p->head;
    for(int i=0;i<p->num;i++){
        record=operate->next;
        free(operate);
        operate=record;
    }
}
int main()
{
    while(1){
        printf("1.入栈\n2.出栈\n3.查看\n4.清空\n");
        Stack s;
        s.num=0;
        int chose;
        scanf("%d",&chose);
        switch(chose){
            case 1:
                printf("请输入数据\n");
                int n;
                scanf("%d",&n);
                insert(&s,n);
                break;
            case 2:
                if(rm(&s)==1){
                    printf("出栈成功\n");
                }
                break;
            case 3:
                look(&s);
                break;
            case 4:
                del(&s);
                exit(0);
                break;
        }
    }
}
