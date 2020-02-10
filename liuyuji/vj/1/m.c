/*************************************************************************
	> File Name: m.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月22日 星期三 15时04分15秒
 ************************************************************************/

#include<stdio.h>
void main()
{
    int n;
    while(scanf("%d",&n)!=EOF){
        int m=n+1;
        if(m%2 == 0){
            printf("%d\n",m/2);
        }
        else{
            printf("%d\n",m);
        }
    }
}
