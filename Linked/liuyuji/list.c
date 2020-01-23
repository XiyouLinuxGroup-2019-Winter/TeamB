/*************************************************************************
	> File Name: list.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月22日 星期三 20时46分04秒
 ************************************************************************/

#include<stdio.h>
#include"list.h"
#include<stdlib.h>
int main()
{
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
    return 0;
}
