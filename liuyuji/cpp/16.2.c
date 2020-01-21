/*************************************************************************
	> File Name: 16.2.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月20日 星期一 16时34分03秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
void show(const double a[],int n);
double* new(int n,...);
int main()
{
    double* p1;
    double* p2;
    p1=new(5,1.2,2.3,3.4,4.5,5.6);
    p2=new(4,1.2,4.3,7.6,9.9);
    show(p1,5);
    show(p2,4);
    free(p1);
    free(p2);
    return 0;
}
void show(const double a[],int n)
{
    for(int i=0;i<n;i++){
        printf("%.1lf ",a[i]);
    }
    printf("\n");
}
double* new(int n,...)
{
    double* p;
    p=(double*)malloc(n*sizeof(double));
    va_list ap;
    va_start(ap,n);
    for(int i=0;i<n;i++){
        p[i]=va_arg(ap,double);
    }
    va_end(ap);
    return p;
}
