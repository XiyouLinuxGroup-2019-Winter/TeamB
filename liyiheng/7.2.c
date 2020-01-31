#include<stdio.h>
int main()
{
   char ch;
    int count=1;
    ch = getchar();
    while(ch!='#')
    {
       putchar(ch);
        printf("%d",ch);
        count++;
        if(count%8==0)
        printf("\n");
        
        
    }
    return 0;
}
