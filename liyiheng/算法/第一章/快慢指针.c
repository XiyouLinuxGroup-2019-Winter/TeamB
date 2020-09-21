#include<stdio.h>
#include<stdlib.h>

void listtail();
struct  Node{
    int val;
    struct Node* next;
}

int main()
{
    int n;
    int i;
    int j;
    printf("请输入插入数的个数：\n");
    scanf("%d",&n);
    for(i = 1;i <= n;i++)
    {
        scanf("%d",j);
        listtail();
    }

}

void listtail()
{

}
