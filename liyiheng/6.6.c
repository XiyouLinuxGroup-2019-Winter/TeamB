#include<stdio.h>
#include<math.h>
int main()
{
   int a,b,i,c,d,k=0,f;
    printf("Enter lower and upper integer limits:\n");
    
    while(scanf("%d %d",&a,&b)==2&&a<b)
    {
       
        {
           for(i=a;i<=b;i++)
            {
              f=pow(i,2);
              k=k+f;
            }
            c=pow(a,2);
            d=pow(b,2);
           printf("The sums of the squares from %d to %d is %d\n",c,d,k);
        }
        
        
        printf("Enter next set of limits:\n");
    }
    printf("Done\n");
}

