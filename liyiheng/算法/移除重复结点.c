/*************************************************************************
	> File Name: 移除重复结点.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月29日 星期三 21时32分46秒
 ************************************************************************/

#include<stdio.h>
truct ListNode* removeDuplicateNodes(struct ListNode* head){
        struct ListNode* q = NULL;
        struct ListNode* p = NULL;
        struct ListNode* t = NULL;

        if(NULL == head)
    {
                return head;
            
    }

    t = head;
        q = t->next;
        
        while(NULL != q)
    {
                
                p = head;
                while(1)
        {
                        
                        if(p->val == q->val)
            {
                                t->next = q->next;
                                free(q);
                                q = t->next;
                                break;
                            
            }
                        
                        
                        if(p->next == q)
            {
                                q = q->next;
                                t = t->next;
                                break;
                            
            }
                        p = p->next;
                    
        }
            
    }

        return head;
}
