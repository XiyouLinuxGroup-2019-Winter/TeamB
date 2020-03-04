/*************************************************************************
	> File Name: list.h
	> Author: 
	> Mail: 
	> Created Time: 2020年01月22日 星期三 19时42分53秒
 ************************************************************************/

#ifndef _LIST_H
#define _LIST_H
#include <stdlib.h>
#include <string.h>
typedef struct student{
	char num[10];
	char name[10];
	char age[10];
	char sex[5];
	char bir[7];
	char place[10];
	char pn[12];
	struct student* next;
}stu;
void input();
void look();
void seek();
void modify();
void del();
void fr();
void sort();
struct student* head=NULL;
struct student* record;
struct student* operate;
int n;
#endif
