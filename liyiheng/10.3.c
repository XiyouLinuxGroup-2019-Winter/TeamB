#include<stdio.h>
#define size 10
int max(double a[]);
int main()
{ 
 
  int i,m;
  double a[size];
  for(i=1;i<size;i++)
    scanf("%lf",&a[i]);
   m=max(a);
    printf("%d\n",m);
}




int max(double a[])
{
   int j,n,i;
    double max=0;
    for(j=1;j<size;j++)
      {
          if(max<a[j])
          {
              max=a[j];
              i=j;
          }
      }
    return i;
}
         

