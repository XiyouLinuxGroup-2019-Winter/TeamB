#include<stdio.h>
#define side 10
int max(int *p);
int main()
{
   int i,a[side],m;
    for(i=1;i<side;i++)
    scanf("%d",&a[i]);
    int (*pf)(int a[]);
    pf=&max;
    m=(*pf)(a);
    printf("max=%d\n",m);
}

int max(int *p)
{
  int t=*p,i;
    for(i=1;i<side;i++)
  if(t<*(p+i))
    t=*(p+i);
    return t;
}


