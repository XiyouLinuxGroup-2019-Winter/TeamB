#include<stdio.h>
double min(double x,double y);
int main()
{
    double x,y,n;
    scanf("%lf %lf",&x,&y);
    n=min(x,y);
    printf("%lf\n",n);
   return 0;
}



double min(double x,double y)
{
   
    double m;
    if(x<y)
    m=x;
    else
    m=y;
    return m;

}
