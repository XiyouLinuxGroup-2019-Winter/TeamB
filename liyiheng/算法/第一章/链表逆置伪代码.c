/*************************************************************************
	> File Name: 链表逆置伪代码.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月28日 星期二 19时13分32秒
 ************************************************************************/

#include<stdio.h>
struct ListNode* reverseList(struct ListNode* head){
        
        struct ListNode* p ;
        struct ListNode* q;
        struct ListNode* r=(struct ListNode*)malloc(sizeof(struct ListNode));
        r -> next= head;
        r -> val = NULL;
        
        p = r -> next;
        r -> next = NULL;
        
        while(p)
    {
               q = p -> next;
               p -> next = r -> next;
               r -> next = p;
               p = q;
            
    }
        
        
        return r -> next;
           



}
