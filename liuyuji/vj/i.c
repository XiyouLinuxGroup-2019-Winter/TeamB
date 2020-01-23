/*************************************************************************
	> File Name: i.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月22日 星期三 13时47分10秒
 ************************************************************************/

#include<stdio.h>
void main()
{
    int n,k;
    scanf("%d",&n);
    scanf("%d",&k);
    int a[n];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    int p=-1;
    for(int i=0;i<n;i++){
        if(k>=a[i]){
            p=i;
        }
        else{
            break;
        }
    }
    int q=-1;
    for(int i=n-1;i>=0;i--){
        if(k>=a[i]){
            q=i;
        }
        else{
            break;
        }
    }
    if(p==n-1 && q==0){
        printf("%d",n);
    }
    else if(p==-1 && q==-1){
        printf("0");
    }
    else if(p==-1 && q!=n){
        printf("%d",n-q);
    }
    else if(p>=0 && q==-1){
        printf("%d",p+1);
    }
    else{
        printf("%d",n-q+p+1);
    }
}
