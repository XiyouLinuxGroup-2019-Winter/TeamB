/*************************************************************************
	> File Name: list.h
	> Author: 
	> Mail: 
	> Created Time: 2020年02月19日 星期三 14时21分36秒
 ************************************************************************/

#ifndef _LIST_H
#define _LIST_H

#include<stdlib.h>
#include<string.h>
typedef struct node{
    struct node* prev;
    struct node* next;
    int data;
}Node;
typedef struct Head{
    Node* head;
    Node* last;
    int size;
}Head;
void input(Head* p);
void print(Head* p);
void sort(Head* p);
void del(Head* p);
Node* find(Head* p);
void fr(Head* p);
void change(Head* p);
void fanzhuan(Head* p);

#endif
