#include<stdio.h>
double larger_of(double x,double y);
int main()
{
  double x,y;
    printf("请输入两个数：\n");
    scanf("%lf %lf",&x,&y);
  printf("%lf %lf\n", larger_of(x,y));
    return 0;

}


double  larger_of(double x,double y)
{
    if(x>y)
    {
      x=x;
      y=x;
    }
    else
    {
      x=y;
      y=y;
    }
    return x,y;
}

