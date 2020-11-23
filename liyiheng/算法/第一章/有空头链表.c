#include<stdio.h>
#include<stdlib.h>
#define data 10

struct Node
{

        int a;
        struct Node *next;

};


struct Node* list_head = NULL;
struct Node* list_end =NULL;


void chushihualisthead()//初始化空头节点
{
    list_head = (struct Node*)malloc(sizeof(struct Node));
    list_head -> next = NULL;
    list_end = list_head;
}

struct Node* creatlist(int a)//创建节点
{
    struct Node*temp = (struct Node*)malloc(sizeof(struct Node));
    if(temp == NULL)
    {
        printf("you faile\n");
        return NULL;
    }

    temp -> a = a;
    temp -> next = NULL;
    return temp;
}


void listtail(int a)//尾插法
{
    struct Node* temp = creatlist(a);
    if(temp == NULL)
    {
        printf("内存不足\n");
        
    }

    list_end -> next = temp;
    list_end = temp;

}


void listhead(int a)//头插法
{
    struct Node* temp = creatlist(a);
    if(temp == NULL)
    {
        printf("内存不足\n");
        
    }

    temp -> next = list_head -> next;
    list_head -> next = temp;

}


void checklist()//遍历
{
    struct Node*temp = list_head -> next;
    
    while(temp != NULL)
    {
        printf("%d ",temp -> a);
        temp = temp -> next;
    }
    printf("\n");
}


struct Node*  findlist(int a)//查找链表
{
    struct Node*temp = list_head -> next;
    while(temp != NULL)
    {
       if(a == temp-> a)
        {

          return temp;

        }
       temp = temp -> next;
    }
     return NULL;
}


void addlistrand(int loction,int a)//任意位置插入链表
{
    if(list_head -> next == NULL)
    {
        printf("无数据\n");
    }
    struct Node*pt = findlist(loction);

    if(pt == NULL)
    {
        printf("查无此节点\n");
    }

    struct Node*temp = creatlist(a);
    if(pt == list_end)
    {
        listtail(a);
    }

    else
    {
       
        temp -> next = pt -> next;
        pt -> next = temp;
    }

}


void deletehead()//删除头
{
    if(list_head == NULL)
    {
        printf("没有节点\n");
    }

    struct Node*temp = list_head -> next;
    list_head -> next = list_head -> next -> next;
    free(temp);
}


void deletetail()//尾删除
{
    if(list_head -> next== NULL)
    {
        printf("无节点\n");
    }

    if(list_head -> next == list_end)
    {
        free(list_end);
        list_head -> next = NULL;
        list_end = list_head;
    }

    else
    {
        struct Node * temp = list_head -> next;

        while(temp != NULL)
        {
            if(temp -> next == list_end)
            {
                break;
            }
            temp = temp -> next;
        }    

        free(list_end);
        list_end = temp;
        list_end -> next = NULL;

    }
}

void deleterand(int a)//删除任意节点
{
    if(list_head -> next == NULL)
    {
        printf("没有节点\n");
    }

    struct Node *temp = findlist(a);

    if(temp == NULL)
    {
        printf("没有数据\n");
    }


    if(temp == list_end)
    {
        deletetail();
    }

    else
    {
        struct Node * pt = list_head;
        while(pt != NULL)
        {
            if(temp == pt -> next)
            {
               break;
            }
            pt = pt -> next;
        } 

       pt -> next = temp -> next;
       free(temp);
   
    }   
   
}

void  Freelist()//释放链表
{
    struct Node * temp = list_head;
    while(temp != NULL)
    {
        struct Node* pt = temp;

        temp = temp -> next;
        free(pt);

    }

    list_head = NULL;
    list_end = NULL;
}


int main()
{
    int j,i;
    int m,n;
    int l;

    chushihualisthead();

    for(i=0;i<data;i++)
    {
        scanf("%d",&j);
        listtail(j);
    }

    checklist();
    printf("请输入你想增加数据的位置：");
    scanf("%d",&m);
    printf("请输入你想增加的数字：");
    scanf("%d",&n);


    addlistrand(m,n);

    checklist();
    deletehead();
    checklist();
    deletetail();
    checklist();
    printf("请输入你想删除的数字：\n");
    scanf("%d",&l);
    deleterand(l);
    checklist();
    Freelist();
}
