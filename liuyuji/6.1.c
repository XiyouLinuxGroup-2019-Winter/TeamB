/*************************************************************************
	> File Name: 6.1.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月16日 星期四 22时07分25秒
 ************************************************************************/

#include<stdio.h>
void main()
{
    int i,j,k;
    char a;
    scanf("%c",&a);
    for(i=1;i<=a-64;i++){
        for(j=1;j<=a-64-i;j++){
            printf(" ");
        }
        for(j=1;j<=2*i-1;j++){
            if(j<=i){
                printf("%c",'A'+j-1);
                k=j-1;
            }
            else{
                printf("%c",'A'+k-1);
                k--;
            }
        }
        printf("\n");
    }
}
