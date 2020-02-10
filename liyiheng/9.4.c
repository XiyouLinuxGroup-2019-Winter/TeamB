#include<stdio.h>
double thpjs(double x,double y);
int main()
{
   double x,y,z;
   printf("请输入两个数：\n");
   scanf("%lf %lf",&x,&y);
   printf("所求答案为：\n");
   z=thpjs(x,y);
   printf("%lf\n",z);
   return 0; 

}


double thpjs(double x,double y)
{
   double average,a,b,m;
    a=1/x;
    b=1/y;
    average=(a+b)/2;
    m=1/average;
    return m;
}


