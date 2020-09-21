#include <stdio.h>
#include <stdlib.h>

struct stu
{
    int a;//系数
	int b;//指数
	struct stu *next;
};

typedef struct stu node;

node *build();
void prin(node *head);
node *add(node *ahead,node *bhead);
node *jian(node *ahead,node *bhead);

int main()
{    
	 node *ahead,*bhead,*chead;
	 printf("1:输入多项式\n");
	 printf("2:多项式加法\n");
     printf("3:多项式减法\n");
	 ahead=build();
	 prin(ahead);
	 bhead=build();
	 prin(bhead);
	 printf("加法和\n");
	 chead=add(ahead,bhead);
	 prin(chead);
	 printf("减法差\n");
	 chead=jian(ahead,bhead);
	 prin(chead);
	 return 0;
	
}
node *build()
{
	
     int c,e;
	 node *p,*q,*head;
	 head=(node *)malloc(sizeof(node));
	 printf("输入系数和指数，按0结束\n");
	 scanf("%d %d",&c,&e);
	 q=head;
     while(c!=0)
	 {
		  p=(node *)malloc(sizeof(node));
		  p->a=c;
		  p->b=e;
		  q->next=p;
		  q=p;
		  scanf("%d %d",&c,&e);
		  
	 }
	 p->next=NULL;
	 return(head);
}
void prin(node *head)
{
	node *p,*q;
	int a=1;
	p=head->next;
	if(!p)
	{
	    putchar('0');
	    printf("\n");
	    return;
	}
	 while(p)
	 {
	     if(p->a>0&&a!=1)  printf("+");
		 if(p->a!=1&&p->a!=-1)
		 {
			 printf("%d",p->a);
			 if(p->b==1) printf("x");
			 else if(p->b) printf("x^%d",p->b);
		 }
		 else
		 {
		   if(p->a==1)
		   {
		       if(!p->b) printf("1");
			   else if(p->b==1) printf("x");
			   else  printf("x^%d",p->b);
		   }
		   if(p->a==-1)
		   {
		       if(!p->b) printf("-1");
			   else if(p->b==1) printf("-x");
			   else printf("-x^%d",p->b);
		   }
		 }
		 p=p->next;
		 a++;
	 }
	 printf("\n");
}
node *add(node *ahead,node *bhead)
{
     node *chead,*pc,*qc,*qa,*qb;
	 chead=(node *)malloc(sizeof(node));
	 qc=chead;
	 qa=ahead->next;
	 qb=bhead->next;
	 qc->next=NULL;
	 while(qa!=NULL&&qb!=NULL)
	 {
	      pc=(node *)malloc(sizeof(node));
		  if(qa->b>qb->b)
		  {
		      pc->a=qa->a;
			  pc->b=qa->b;
			  qa=qa->next;
		  }
		  else if(qa->b==qb->b)
		  {
		      pc->a=qa->a+qb->a;
			  pc->b=qa->b;
			  qa=qa->next;
			  qb=qb->next;
		  }
		  else
		  {
		      pc->a=qb->a;
			  pc->b=qb->b;
			  qb=qb->next;
		  }
		  if(pc->a!=0)
		  {
		     qc->next=pc;
			 qc=pc;
		  }
		  else
			  free(pc);
		  
	 }
	 while(qa!=NULL)
	 {
	     pc=(node *)malloc(sizeof(node));
		 pc->a=qa->a;
		 pc->b=qa->b;
		 qc->next=pc;
		 qa=qa->next;
		 qc=pc;
	 }
	 while(qb!=NULL)
	 {
	     pc=(node *)malloc(sizeof(node));
		 pc->a=qb->a;
		 pc->b=qb->b;
		 qc->next=pc;
		 qb=qb->next;
		 qc=pc;
	 }
      qc->next=NULL;
	 return chead;
}
node *jian(node *ahead,node *bhead)
{
    node *p,*q;
	p=bhead->next;
	q=bhead->next;
	while(p)
	{
	   p->a=p->a*-1;
	   p=p->next;
	}
	p=add(ahead,bhead);
	while(q)
	{
	   q->a=q->a*-1;
	   q=q->next;
	}
	return p;
}
