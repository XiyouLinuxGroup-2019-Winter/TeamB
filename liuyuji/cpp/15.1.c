/*************************************************************************
	> File Name: 15.1.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月18日 星期六 14时54分31秒
 ************************************************************************/

#include<stdio.h>
int s(char * p);
void main()
{
    char p[100];
    scanf("%s",p);
    printf("%d",s(p));
}
int s(char * p)
{
    int i=0;
    while(p[i]!=0){
        i++;
    }
    i--;
    int l=i;
    int k=0;
    int q=1;
    int j;
    for(;i>=0;i--){
        q=1;
        for(j=1;j<=l-i;j++){
            q*=2;
        }
        k=k+q*(p[i]-48);
    }
    return k;
}
