/*************************************************************************
	> File Name: s.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月22日 星期三 15时26分38秒
 ************************************************************************/

#include<stdio.h>
void main()
{
    int n;
    scanf("%d",&n);
    int a[n];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n-1;i++){
        int k;
        int l=n;
        k=0;
        for(int j=0;j<l;j++){
            if(a[j]>a[j+1]){
                int sum=a[j]+a[j+1];
                a[j]=sum-a[j];
                a[j+1]=sum-a[j+1];
                k=j;
            }
        }
        l=k;
        if(k==0){
            break;
        }
    }
    if(n%2 != 0){
        printf("%d",a[n/2]);
    }
    else{
        int k=(int)n/2-1;
        printf("%d",a[k]);
    }
}
