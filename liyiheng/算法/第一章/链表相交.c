/*************************************************************************
	> File Name: 链表相交.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月29日 星期三 19时58分24秒
 ************************************************************************/

#include<stdio.h>
truct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
        struct ListNode* p = headA;
        struct ListNode* q = headB;

        while(p!=NULL)
    {
                q=headB;
                while(q)
        {
                        if(q==p)
                        return q;
                        else
                        q=q->next;
                    
        }
                p=p->next;
            
    }
        return NULL;



}
