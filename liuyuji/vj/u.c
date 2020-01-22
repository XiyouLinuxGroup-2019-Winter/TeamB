/*************************************************************************
	> File Name: u.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月22日 星期三 16时19分18秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
void main()
{
    char a[500000];
    scanf("%s",a);
    int i=0;
    int k[2];
    int b[2];
    while(a[i]!=0){
        if(a[i]==91){
            while(a[i]!=0){
                if(a[i]==58){
                    b[0]=i;
                    k[0]=1;
                    break;
                }
                i++;
            }
            break;
        }
        i++;
    }
    i=strlen(a);
    i--;
    while(i>=0){
        if(a[i]==93){
            while(i>=0){
                if(a[i]==58){
                    b[1]=i;
                    k[1]=1;
                    break;
                }
                i--;
            }
            break;
        }
        i--;
    }
    if(b[1]!=b[0] && k[0]==k[1]==1){
        int sum=0;
        i=b[0];
        while(i<=b[1]){
            if(a[i]==124){
                sum++;
            }
            i++;
        }
        printf("%d",sum+4);
    }
    else{
        printf("-1");
    }
}
