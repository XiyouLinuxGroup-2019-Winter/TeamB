/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月06日 星期一 16时36分54秒
 ************************************************************************/

#include<stdio.h>
#define j 60;
void main()
{
    while(1){
        int a;
        scanf("%d",&a);
        if(a>=0){
            int h,m;
            h=(int)a/j;
            m=a%j;
            printf("%dh%dm\n",h,m);
        }
        else{
            break;
        }
    }
}
