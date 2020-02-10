#include<stdio.h>
void lll(char ch,int i,int j);
int main(void)
{
    int i,j;
    char ch;
    printf("请输入你想打印的行数:\n");
    scanf("%d",&i);
    printf("请输入你想打印的次数:\n");
    scanf("%d",&j);
    printf("请输入你想打印的字符:\n");
    scanf("%c",&ch);
    ch=getchar();
    lll(ch,i,j);
    return 0;
}


void lll(char ch,int i,int j)
{
    int n=0,m=0;
    for(n=0;n<i;n++)
     {
         for(m=0;m<j;m++)
         printf("%c",ch);
         printf("\n");
     }
}

