/*************************************************************************
	> File Name: 链表相交2.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月29日 星期三 20时24分27秒
 ************************************************************************/

#include<stdio.h>
truct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
        if (headA == NULL || headB == NULL)
            return NULL;
        struct ListNode* La = headA,*Lb = headB;
        while (La != Lb)
    {
                La = La == NULL ? headB : La->next;
                Lb = Lb == NULL ? headA : Lb->next;
            
    }
        return La;

}


