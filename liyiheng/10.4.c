#include<stdio.h>
#define size 10
double value(double a[]);
int main()
{
  double a[size],k;
    int i;
    for(i=0;i<size;i++)
     scanf("%lf",&a[i]);
    k=value(a);
    printf("%lf\n",k);

}

double  value(double a[])
{
    double max=0,min=0,cz,x;
    int i,j;
    for(i=0;i<size;i++)
      {
         if(a[i]>max)
          {
              max=a[i];
          }
      }
    for(i=0;i<size;i++)
      for(j=0;j<size-1-i;j++)
        {  
              if(a[j]>a[j+1])
                {
                  x=a[j];
                  a[j]=a[j+1];
                  a[j+1]=x;
                }
        }          
      min=a[0];
     cz=max-min;
     return cz;
}



        

