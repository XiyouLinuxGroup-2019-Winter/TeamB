/*************************************************************************
	> File Name: 9_2.c
	> Author: 
	> Mail: 
	> Created Time: 2020年09月20日 星期日 21时34分33秒
 ************************************************************************/

#include<stdio.h>
#include<stdio.h>
int i=0,n=0,m=0;
struct stud
{
        int a;
        struct stud *next;

};
struct stud *jianli()
{ 
    struct stud *p1,*p2,*head;
    head=p2=(struct stud *)malloc(sizeof(struct stud));
    p1=(struct stud*)malloc(sizeof(struct stud));
    printf("请输入数据(0结束)：\n"); 
    scanf("%d",&p1->a);
    while(p1->a!=0)
    {
                i++;
                p2->next=p1;
                p2=p1;
                p1=(struct stud*)malloc(sizeof(struct stud));
                printf("请输入数据(0结束)：\n"); 
                scanf("%d",&p1->a);
             
    } 
    p2->next=NULL;
    free(p1);
    return head;
}

struct stud *hecheng(struct stud *A,struct stud *B) 
{
        struct stud *q1,*q2,*p3,*p4,*headc;
        q1=A->next;
        q2=B->next;
        headc=p4=(struct stud *)malloc(sizeof(struct stud));
        p3=(struct stud*)malloc(sizeof(struct stud));
        if(m<=n)
    {
                    printf("1");
                while(q1!=NULL)
        {
                        p3->a=q1->a;
                        q1=q1->next;
                        p4->next=p3;
                        p4=p3;
                        p3=(struct stud*)malloc(sizeof(struct stud));
                        p3->a=q2->a;
                        q2=q2->next;
                        p4->next=p3;
                        p4=p3;
                        p3=(struct stud*)malloc(sizeof(struct stud));
                    
        }
                p4->next=q2;
                return headc;
            
    }

        while(q2!=NULL)
    {
                
                    p3->a=q2->a;
                    q2=q2->next;
                    p4->next=p3;
                    p4=p3;
                    p3=(struct stud*)malloc(sizeof(struct stud));
                    p3->a=q1->a;
                    q1=q1->next;
                    p4->next=p3;
                    p4=p3;
                    p3=(struct stud*)malloc(sizeof(struct stud));
                
    }
            p4->next=q1;
            return headc;

}
struct stud *dayin(struct stud *head)
{
        struct stud *d;
        d=head->next;
        while(d!=NULL)
    {
                printf("%d ",d->a);
                d=d->next; 
            
    }
        printf("\n");

}
main()
{
        struct stud *A,*B,*C; 
        printf("创建第一个链表\n");
        A=jianli();
        dayin(A);
        m=i;
        i=0;
        printf("创建第二个链表\n");
        B=jianli();
        dayin(B);
        n=i;
        printf("合成第三个链表\n");
        C=hecheng(A,B);
        dayin(C);
        

}
