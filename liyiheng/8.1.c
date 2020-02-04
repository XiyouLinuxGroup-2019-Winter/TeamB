#include<stdio.h>
int main(void)
{
    char ch;
    int count=0;
    while(ch=getchar()!='&')
    
        count++;
    
    printf("%d",count);
    return 0;
}


   
