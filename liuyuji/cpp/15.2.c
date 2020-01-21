/*************************************************************************
	> File Name: 15.2.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月18日 星期六 15时27分05秒
 ************************************************************************/

#include<stdio.h>
int s(int a);
void main()
{
    int a;
    scanf("%d",&a);
    printf("\n%d",s(a));
}
int s(int a)
{
    int b,i,j,k;
    k=i=0;
    int c[8];
    while(a!=0){
        int b=a%2;
        a=(int)a/2;
        c[i]=b;
        i++;
    }
    for(j=0;j<=i-1;j++){
        if(c[j]==1){
            k++;
        }
        printf("%d",c[j]);
    }
    return k;
}
