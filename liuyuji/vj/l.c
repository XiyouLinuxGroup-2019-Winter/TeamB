/*************************************************************************
	> File Name: l.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月22日 星期三 14时44分21秒
 ************************************************************************/

#include<stdio.h>
void main()
{
    int n,sum;
    while(scanf("%d",&n)!=EOF){
        int a=n/2;
        sum=0;
        for(int i=1;i<a;i++){
            sum+=i;
        }
        if(n%2==0){
            printf("%d\n",2*sum);
        }
        else{
            printf("%d\n",2*sum+a);
        }
    }
}
