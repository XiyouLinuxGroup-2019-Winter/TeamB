#include <stdio.h>
#include <stdlib.h>

struct xishu
{
    int a;
	int b;
	struct xishu *next;
};

typedef struct xishu qq;

void shuchu(qq *head);
qq *shuru();
qq *jiaf(qq *ahead,qq *bhead);
qq *jianf(qq *ahead,qq *bhead);

int main()
{
     
	 qq *ahead,*bhead,*chead;
     printf("来了\n");
    printf("了");
    
	 ahead=shuru();
	 shuchu(ahead);
	 bhead=shuru();
	 shuchu(bhead);
	 printf("两者相加\n");
	 chead=jiaf(ahead,bhead);
	  shuchu(chead);
	  printf("两者相减\n");
	 chead=jianf(ahead,bhead);
	 shuchu(chead);
	 return 0;
}

qq *shuru()
{
	 int c,e;
	 qq *p,*q,*head;
	 head=(qq *)malloc(sizeof(qq));
	 
	 scanf("%d %d",&c,&e);
	 q=head;
     while(c!=0)
	 {
		  p=(qq *)malloc(sizeof(qq));
		  p->a=c;
		  p->b=e;
		  q->next=p;
		  q=p;
		  scanf("%d %d",&c,&e);
		  
	 }
	 
	 p->next=NULL;
	 return(head);

}

qq *jiaf(qq *ahead,qq *bhead)
{
	 qq *chead,*pc,*qc,*qa,*qb;
	 chead=(qq *)malloc(sizeof(qq));
	 qc=chead;
	 qa=ahead->next;
	 qb=bhead->next;
	 qc->next=NULL;
	 while(qa!=NULL&&qb!=NULL)
	 {
	      pc=(qq *)malloc(sizeof(qq));
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
	     pc=(qq *)malloc(sizeof(qq));
		 pc->a=qa->a;
		 pc->b=qa->b;
		 qc->next=pc;
		 qa=qa->next;
		 qc=pc;
	 }
	 while(qb!=NULL)
	 {
	     pc=(qq *)malloc(sizeof(qq));
		 pc->a=qb->a;
		 pc->b=qb->b;
		 qc->next=pc;
		 qb=qb->next;
		 qc=pc;
	 }
      qc->next=NULL;
	 return chead;
}

void shuchu(qq *head)
{
     qq *p,*q;
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

qq *jianf(qq *ahead,qq *bhead)
{
    qq *p,*q;
	p=bhead->next;
	q=bhead->next;
	while(p)
	{
	   p->a=p->a*-1;
	   p=p->next;
	}
	p=jiaf(ahead,bhead);
	while(q)
	{
	   q->a=q->a*-1;
	   q=q->next;
	}
	return p;
}
