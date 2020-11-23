#include<stdio.h>
#include<stdlib.h>

typedef struct NODE{
    int data;
    struct NODE *next;
}*L,la;

L creat()
{
    L   p,q,t;
    int n,i;
    p = (L)malloc(sizeof(la));
    p -> data = 1;
    t = p;
    while((i == scanf("%d",&n) != EOF))
    {
        q = (L)malloc(sizeof(la));
        q -> data = n;
        p -> next = q;
        q -> next = NULL;
        p = q;
        
        printf("结束请输入数字０\n");
        if(n == 0)
        break;
    }

    return t;
}

void checklist(L p)
{
    L m;
    m = p;
    while((m -> next) != NULL)
    {
        printf("%d",m -> data);
        printf(" ");
        m = m -> next;
    }
    printf("\n");
}

L delete_paste(L q,L p,int i,int j,int len)
{
    int m,n,t;
    L p2,q2,p3,q3;
    p2 = p;
    p3 = p;
    q2 = q;
    q3 = q;

    for(m = 1;m < i;m++)
    p2 = p2 -> next;

    for(n = 1;n < j; n++)
    q2 = q2 -> next;

    for(t = 1;t < len + i; t++)
    p3 = p3 -> next;

    p3 -> next = q2 -> next;
    q2 -> next = p2;

    return q;
}

L delete_paste2(L q,L p,int i,int j, int len)
{
    int m,n,t;
    L p2,q2,p3,q3;
    p2 = p;
    p3 = p;
    q2 = q;
    q3 = q;

    for(m = 1;m < i;m++)
    p2 = p2 -> next;

    for(n = 1;n < j;n++)
    q2 = q2 -> next;
    for(t = 1; t < len + i;t++)
    p3 = p3 -> next;

    p2 -> next = p3 -> next;
    return p;
}

int main()
{
    L  p,q,q2,p2;
    int i,j,len;
    printf("请创建表a\n");
    p = creat();//创建ａ链
    printf("表a输出结果：\n");
    checklist(p) ;
    printf("请创建表b\n");
    q = creat();//创建ｂ链
    printf("表b输出结果:\n");
    checklist(q);
    printf("请输入你想删除a表第几个元素，共删除几个：\n");
    scanf("%d",&i);
    scanf("%d",&len);
    printf("请输入你想在b链插入的位置：\n");
    scanf("%d",&j);
    q2 = delete_paste(p,q,i,j,len);
    checklist(q2);
    p2 = delete_paste2(p,q,i,j,len);
    checklist(p2);
}


