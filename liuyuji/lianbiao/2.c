/*************************************************************************
	> File Name: 2.c (双向循环链表)
	> Author: 
	> Mail: 
	> Created Time: 2020年01月22日 星期三 17时26分46秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int n;
    struct node* before;
    struct node* after;
}Node;
int main()
{
    Node *head,*record,*operate;
    head=NULL;
    while(1){
        int a;
        scanf("%d",&a);
        if(a<0){
            break;
        }
        operate=(Node*)malloc(sizeof(Node));
        if(head==NULL){
            head=operate;
            operate->before=NULL;
            operate->after=NULL;
        }
        else{
            record->after=operate;
        }
        if(head!=operate){
            head->before=operate;
            operate->before=record;
            operate->after=head;
        }
        operate->n=a;
        record=operate;
    }
    operate=head;
    do{
        printf("%d",operate->n);
        operate=operate->after;
    }while(operate->after!=head);
    printf("%d\n",operate->n);
    operate=head->before;
    do{
        printf("%d",operate->n);
        operate=operate->before;
    }while(operate!=head);
    printf("%d",operate->n);
    operate=head;
    while(operate->after!=head){
        record=operate->after;
        free(operate);
        operate=record;
    }
    return 0;
}
