#include<stdio.h>
#include<math.h>
int main()
{
    int n,i,a,b,c;
    scanf("%d",&n);
    for(i=0;i<n;i++)
     {
         scanf("%d",&a);
         b = pow(a,2);
         c = pow(a,3);
         printf("%d %d %d\n",a,b,c);
     }
}

