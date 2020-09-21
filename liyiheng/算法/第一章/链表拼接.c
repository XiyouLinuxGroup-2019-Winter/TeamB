#include<stdio.h>
#include<stdlib.h>


typedef struct node{
    int data;
    struct node* next;
}node;


node* Connect(node* A,node* B)
{
        node* p = A->next;
        
        A->next = B->next->next;
        
        free(B->next);
        
        B->next = p -> next;
        
        return B;

} 

node* create1(int n)
{
    node *p = NULL,*head;
    head = (node*)malloc(sizeof(node));
    p = head;
    node *s;
    int i = 1;
    while(n)
    {
      s = (node*)malloc(sizeof(node));
      s -> data = i++;
      p -> next = s;
      p = s;
      n--;
    }
    s -> next = head;
    return s;
}

node* create2(int m)
{
    node *p = NULL,*head;
    head = (node*)malloc(sizeof(node));
    p = head;
    node *s;
    int j = 100;
    while(m)
    {
        s = (node*)malloc(sizeof(node));
        s -> data = j++;
        p -> next = s;
        p = s;
        m--;
    }
    s ->next = head;
    return s;
}

int main()
{
    node *A;
    node *B;
    node *C;
    int m,n,k;
    
    
    printf("请输入两个数：\n");
    scanf("%d %d",&n,&m);
    k = m + n;
    A = create1(n);
    B = create2(m);

    C = Connect(A,B);

    for(int i = 0;i < k;i++)
    {
        printf("%2d",C->data);
    }
    printf("\n");
}



