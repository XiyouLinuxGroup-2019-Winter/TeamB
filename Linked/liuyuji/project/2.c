/*************************************************************************
	> File Name: 3.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月19日 星期三 14时18分08秒
 ************************************************************************/

#include<stdio.h>
#include"list.h"
int main()
{
        Head inode;//创建inode记录链表信息
        inode.head=inode.last=NULL;
        inode.size=0;
        Head* p=&inode;
    while(1){
        printf("请选择您的操作\n1.增加节点\n2.查看信息\n3.删除节点\n4.搜索节点\n5.修改节点\n6.反转链表\n7.退出\n");
        int a;
        scanf("%d",&a);
        switch(a){
            case 1:input(p);break;
            case 2:print(p);break;
            case 3:del(p);break;
            case 4:find(p);break;
            case 5:change(p);break;
            case 6:fanzhuan(p);break;
            case 7:fr(p);break;
        }
    }
}
void input(Head* p)
{
    Node *operate,*record;
    operate=record=NULL;
    operate=(Node*)malloc(sizeof(Node));
    printf("请输入节点内容\n");
    int temp;
    scanf("%d",&temp);
    if(p->head==NULL){
        p->head=operate;
        p->last=operate;
        p->size=1;
    }
    else{
        record=p->last;
        record->next=operate;
        operate->next=p->head;
        operate->prev=record;
        p->size++;
        p->last=operate;
    }
    operate->data=temp;
    sort(p);
}
void print(Head* p)
{
    Node *operate=NULL;
    printf("1.正序打印\n2.逆序打印\n");
    int n;
    scanf("%d",&n);
    if(n==1){
        operate=p->head;
        for(int i=1;i<=p->size;i++,operate=operate->next){
            printf("%d ",operate->data);
        }
    }
    if(n==2){
        operate=p->last;
        for(int i=p->size;i>=1;i--,operate=operate->prev){
            printf("%d ",operate->data);
        }
    }
    printf("\n");
}
void sort(Head* p)
{
    Node *operate,*record;
    if(p->size>1){
        for(int i=1;i<p->size;i++){
            operate=p->head;
            record=operate->next;
            for(int j=1;j<p->size;j++){
                if(operate->data>record->data){
                    int sum=operate->data+record->data;
                    operate->data=sum-operate->data;
                    record->data=sum-record->data;
                }
                operate=operate->next;
                record=record->next;
            }
        }
    }

}
void del(Head* p)
{
    Node* operate=find(p);
    Node* record=NULL;
    printf("确定删除？\n1.yes\n2.no\n");
    int n;
    scanf("%d",&n);
    if(n==1){
        record=operate->prev;
        record->next=operate->next;
        record=operate->next;
        record->prev=operate->prev;
        free(operate);
        p->size--;
    }
}
Node* find(Head* p)
{
    Node* operate=NULL;
    printf("请输入要查看的节点序数");
    int n;
    scanf("%d",&n);
    operate=p->head;
    for(int i=2;i<=n;i++){
        operate=operate->next;
    }
    printf("第%d个节点内容为%d\n",n,operate->data);
    return operate;
}
void fr(Head* p)
{
    Node* operate=p->head;
    Node* record=NULL;
    for(int i=1;i<=p->size;i++){
        record=operate;
        free(operate);
        operate=record->next;
    }
    exit(0);
}
void change(Head* p)
{
    Node* operate=find(p);
    printf("请输入修改后的数据\n");
    int temp;
    scanf("%d",&temp);
    operate->data=temp;
    sort(p);
}
void fanzhuan(Head* p)
{
    Node *operate,*record;
    operate=p->head;
    for(int i=0;i<p->size;i++){
        record=operate->next;
        operate->next=operate->prev;
        operate->prev=record;
        operate=record;
    }
    record=p->head;
    p->head=p->last;
    p->last=record;
}
