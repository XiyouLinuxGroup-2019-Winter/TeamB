#include<stdio.h>
#include<stdlib.h>


typedef struct node{
    int data;
    struct node* next;
}node;


node* creat(int n)
{
    node *p = NULL,*head;
    head = (node*)malloc(sizeof(node));
    p = head;
    node *s;
    int i = 1;
    if(n != 0)
    {
        while(i <= n)
        {
           s = (struct node*)malloc(sizeof(struct node));
           s -> data = i++;
           p -> next = s;
           p = s;
        }
        s -> next = head -> next;
        free(head);
        return s -> next;
    }
}

int main()
{
    int n = 41;
    int m = 3;
    node* p = creat(n);
    node* temp;

    m =m%n;

    while(p != p -> next)
    {
        for(int i = 1; i < m - 1;i++)
        {
            p = p -> next;
        }
        
        printf("%d->",p -> next -> data);

        temp = p -> next;
        p -> next = temp -> next;
        free(temp);

        p = p -> next;
    }
    printf("%d\n",p -> data);
    return 0;
}

    
