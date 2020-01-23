/*************************************************************************
	> File Name: o.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月22日 星期三 15时13分00秒
 ************************************************************************/

#include<stdio.h>
void main()
{
    char a[1005];
    int b;
    while(scanf("%s",a)!=EOF){
        int i=0;
        b=0;
        if(a[0]=='0'){
            continue;
        }
        while(1){
            i=0;
            b=0;
            while(a[i]!=0){
                b=b+a[i]-48;
                i++;
            }
            if(b%10==b){
                printf("%d\n",b);
                break;
            }
            else{
                for(i=0;i<1005;i++){
                    a[i]=0;
                }
                sprintf(a,"%d",b);
            }
        }
    }
}
