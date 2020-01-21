/*************************************************************************
	> File Name: 8.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月16日 星期四 21时36分19秒
 ************************************************************************/

#include<stdio.h>
double lf(double a);
void main()
{
    double a;
    scanf("%lf",&a);
    printf("%lf",lf(a));
}
double lf(double a)
{
    return a*a*a;
}
