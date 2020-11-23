#include<stdio.h>
#include<stdlib.h>
struct stu
{
    int a;
	struct stu *next;
};

typedef struct stu node;

node *add(node *ahead,node *bhead);
node *build();

node *add(node *ahead,node *bhead)
{
	int m,n;
	node *p,*q,*r,*head;
	p=ahead->next;
	q=bhead->next;
	printf("请输入A，B两链长度\n");
	scanf("%d %d",&m,&n);
	if(m<n)//ahead为短链
	{
	    head=p;
	    p=p->next;
	    r=head;
	    while(q!=NULL&&p!=NULL)
		{
		    r->next=q;
		    r=r->next;
		    q=q->next;
		    r->next=p;
		    r=r->next;
		    p=p->next;
		}
		while(p==NULL&&q!=NULL)
		{
			r->next=q;
			r=r->next;
			q=q->next;
		}
	}
	else
	{

	    head=q;
	    q=q->next;
	    r=head;
	    while(q!=NULL&&p!=NULL)
		{
		    r->next=p;
		    r=r->next;
		    p=p->next;
		    r->next=q;
		    r=r->next;
		    q=q->next;
		}
		while(q==NULL&&p!=NULL)
		{
			r->next=p;
			r=r->next;
			p=p->next;
		}
	}
	return(head);
}
node *build()
{
	int c;
	node *p,*q,*head;
	head=(node *)malloc(sizeof(node));
	scanf("%d",&c);
	q=head;
	while(c!=0)
	{
		p=(node *)malloc(sizeof(node));
		p->a=c;
        q->next=p;
		q=p;
		scanf("%d",&c);
	}
	p->next=NULL;
	return(head);
}
main()
{
	node *ahead,*bhead,*chead;
	ahead=build();
	bhead=build();
	chead=add(ahead,bhead);
}