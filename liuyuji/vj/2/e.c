/*************************************************************************
	> File Name: e.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月11日 星期二 20时01分24秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main()
{
    int n,m;
    while(1){
        scanf("%d %d",&n,&m);
        if(m==0 && n==0){
            break;
        }
        else{
            int tmp[n+1],c[n+1],sum;
            tmp[0]=c[0]=sum=0;
            int dp[m+1];
            memset(dp,0,sizeof(dp));
            dp[0]=1;
            for(int i=1;i<=n;i++){
                scanf("%d",&tmp[i]);
            }
            for(int i=1;i<=n;i++){
                scanf("%d",&c[i]);
                sum+=c[i];
            }
            int v[sum+1];
            v[0]=0;
            for(int i=1;i<=n;i++){
                v[i]=tmp[i];
            }
            for(int i=1;i<=n;i++){
                int k=1;
                if(c[i]>2){
                    int j;
                    for(j=2;j<=c[i]-1;j*=2){
                        v[n+k]=j*v[i];
                        k++;
                    }
                    int l=0;
                    for(int i=1;i<k;i++){
                        int b=1;
                        for(int j=1;j<=i;j++){
                            b*=2;
                        }
                        l+=b;
                    }
                    v[n+k]=(c[i]-l)*v[i];
                    k++;
                }
                if(c[i]==2){
                    v[n+k]=v[i];
                    k++;
                }
            }
            for(int i=1;i<=sum;i++){
                for(int j=m;j>=v[i];j--){
                    if(j>=v[i]){
                        dp[j]=dp[j]+dp[j-v[i]];
                    }
                    else{
                        dp[j]=dp[j];
                    }
                }
            }
            printf("%d\n",dp[sum]);
        }
    }
}
