/*************************************************************************
	> File Name: a.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月10日 星期一 16时36分20秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#define min(a,b) ((a)<(b) ? (a):(b))
int main()
{
    int t;
    scanf("%d",&t);
    for(;t>0;t--){
        int c,n,a,b;
        scanf("%d %d",&a,&b);
        c=b-a;
        scanf("%d",&n);
        int v[n+1];
        int w[n+1];
        int dp[c+1];
        memset(dp,0x3f3f3f,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d %d",&v[i],&w[i]);
        }
        v[0]=w[0]=dp[0]=0;
        for(int i=1;i<=n;i++)
        {
            for(int j=w[i];j<=c;j++)
            {
                dp[j]=min(dp[j],dp[j-w[i]]+v[i]);
            }
        }
        if(dp[c]!=0x3f3f3f)
        {
            printf("The minimum amount of money in the piggy-bank is %d.\n",dp[c]);
        }
        else{
            printf("This is impossible.\n");
        }
    }
    return 0;
}
