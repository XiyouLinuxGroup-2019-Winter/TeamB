/*************************************************************************
	> File Name: a.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月10日 星期一 16时36分20秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#define max(a,b) ((a)>(b) ? (a):(b))
int main()
{
    int t;
    scanf("%d",&t);
    for(;t>0;t--){
        int c,n;
        scanf("%d %d",&n,&c);
        int v[n+1];
        int w[n+1];
        v[0]=w[0]=0;
        int dp[n+1][c+1];
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d",&v[i]);
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
        }
        for(int i=1;i<=n;i++)
	    {
		    for(int j=1;j<=c;j++)
		    {
			    if(j<w[i])
				    dp[i][j]=dp[i-1][j];
			    else
				    dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i]]+v[i]);
		    }
	    }
        printf("%d",dp[n][c]);
    }
    return 0;
}
