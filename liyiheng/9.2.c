#include<stdio.h>
void chline(char ch,int i,int j);
int main()
{
  int x,y;
    printf("请分别输入行与列的个数");
    scanf("%d %d",&x,&y);
    
chline('#',x,y);
    return 0;
}

void chline(char ch,int i,int j)
{
   int n=0,m=0;
    for(n=0;n<i;n++)
    {
      for(m=0;m<j;m++)
          putchar(ch);
    printf("\n");
    }
}
