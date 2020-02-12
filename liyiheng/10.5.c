#include<stdio.h>
#define size 10
void dx(double a[]);
int main()
{
  double a[size];
  int i;

    for(i=0;i<size;i++)
     
         scanf("%lf",&a[i]);
    dx(a);

}

void  dx(double a[])
{
    int i;
    for(i=size-1;i>=0;i--)
    {
      printf("%lf",a[i]);
      if(i!=0)
        printf(" ");
    }
    printf("\n");
}

