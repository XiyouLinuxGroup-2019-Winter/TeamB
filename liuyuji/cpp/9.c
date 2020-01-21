/*************************************************************************
	> File Name: 9.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月16日 星期四 21时42分14秒
 ************************************************************************/

#include<stdio.h>
void Temp(double* a,double* b);
void main()
{
    double a;
    while(1){
        printf("请输入华氏度");
        if(scanf("%lf",&a)==1){
            double b=a;
            Temp(&a,&b);
            printf("摄氏度%lf 开氏度%lf\n",a,b);
        }
        else{
            break;
        }
    }
}
void Temp(double* a,double* b)
{
    *a=5.0/9.0*(*a-32.0);
    *b=*a+273.16;
}
