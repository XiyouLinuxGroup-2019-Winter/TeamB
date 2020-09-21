#include<stdio.h>
#include<stdlib.h>
#define DATA  10

struct Node
{

	int a;
	struct Node *next;
};

struct Node* list_head = NULL;
struct Node* list_end =NULL;

void  listti(int a)//尾插法
{
    struct Node*temp = (struct Node*)malloc(sizeof(struct Node));

    temp -> a = a;
    temp -> next = NULL;


    if(list_head == NULL)
    {
	    list_head = temp;
	    list_end = temp;
    }
    else
    {
	    list_end -> next = temp;
	    list_end = temp;
    }
}


void listhead(int a)//头插法
{
   struct Node*temp = (struct Node*)malloc(sizeof(struct Node));
   temp -> a = a;
   temp -> next = NULL;

   if(list_head == NULL)
   {
	   list_head = temp;
	   list_end = temp;
   }
   else
   {
	   temp -> next = list_head;
	   list_head = temp;
   }
}


struct Node* listfind(int a)//查找特定链表
{
	struct Node* temp = list_head;
	while(temp !=NULL)
	{
		if(a == temp ->a)
		{

		    return temp;
	        }

		temp = temp -> next;
	}
	return NULL;
}


void freelist()//释放链表
{
	struct Node*temp = list_head;
	if(temp != NULL)
	{
		struct Node* pt = temp;
		temp = temp -> next;
		free(pt);
	}
	list_head = NULL;
	list_end =NULL;
}


void addlist(int m,int n)//指定位置插入节点
{
	if(list_head == NULL)
	{
		printf("没有数据！\n");
		return;
	}


	struct Node * pt = listfind(m);
	if(pt == NULL)
	{
		printf("没有节点！");
		return;
	}

	struct Node * temp2 = (struct Node*)malloc(sizeof(struct Node));

	temp2 -> a = n;
	temp2 -> next = NULL;

	if(pt == list_end)
	{
		pt -> next = temp2;
		list_head = temp2;
	}

	else
	{
		temp2 ->next = pt -> next;
		pt -> next = temp2;
	}
}	



void  checklist()//浏览链表
{
	struct Node*temp = list_head;	
	
	while(temp !=NULL)
	{
		printf("%d ",temp -> a);

		temp = temp -> next;
	}
         printf("\n");
}


void  deletehead()//头删除
{
    if(list_head == NULL)
    {
        printf("没有此链表\n");
    }

	if(list_head !=NULL)
	{
		struct Node*pt = list_head;
		list_head = list_head -> next;
		free(pt);
	}

    else if(list_head == list_end)
    {
        free(list_head);
        list_head = NULL;
        list_end = NULL;
    }

	else
	{
		printf("没有此链表\n");
		return;
	}
}


void  deletetail()//尾删除
{
	if(list_head == NULL)
	{
		printf("没有链表\n");
                return;
	}

	if(list_head == list_end)
	{
		free(list_head);
		list_head = NULL;
		list_end =NULL;
		
	}
	else
	{
         struct Node*temp = list_head;

	     while(temp -> next != list_end)
	     {
		     temp = temp -> next;
	     }

	     free(list_end);
	     list_end = temp;
	     list_end -> next= NULL;
	     
	}
}


void deletelistrand(int a)//删除指定节点
{
    if(list_head == NULL)
    {
	    printf("没有此链表\n");
	    return;
    }

    struct Node * temp = listfind(a);

    if(temp == NULL)
    {
	    printf("查无此节点\n");
    }

    if(list_head  == temp)
    {
        deletehead();
    }

    else if(list_end == temp)
    {
          deletetail();
    }
   
   

	else
	{
		struct Node * pt = list_head;
		while(pt ->next != temp)
		{
			pt = pt -> next;
		}
            pt -> next = temp -> next;
		  free(temp);
	}
    
}



int main()
{
	int a[DATA]; 
	int i = 0;
	int n;
	int point,m;
	for(i=0;i< DATA;i++)
		scanf("%d",&a[i]);

	for(i=0;i<DATA;i++)
	{
          listhead(a[i]);
	  
	}

	 checklist();
	 printf("请输入查找的序号:");
	 scanf("%d",&n);
	 struct Node* pfind = listfind(n);
	 if(pfind != NULL)
	 {
		 printf("%d\n",pfind -> a);
	 }
	 else
		 printf("不存在\n");

        
         printf("请输入想在第几个位置插入数据：");
	 scanf("%d",&point);
	 printf("请输入插入的数据：");
	 scanf("%d",&m);

         addlist(point,m);
	 printf("打印插入后的数据：\n");

	 checklist();
	 printf("删除一个数据后的数据：\n");
         deletehead();
	 checklist();
         printf("删除最后一个数据后的数据：\n");
	 deletetail();
	 checklist();
	 int k;
	 printf("请输入你想删除的数据：\n");
	 scanf("%d",&k);
	 deletelistrand(k);
	 checklist();


	 freelist();


}

	    
   
