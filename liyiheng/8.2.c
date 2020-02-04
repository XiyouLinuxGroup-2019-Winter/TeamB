#include<stdio.h>
int main()
{
  int  big=0;
  int  small=0;
  char ch;
  while((ch = getchar())!='&')
    {
        if(ch>='A'&&ch<='Z')
         big++;
        if(ch>='a'&&ch<='z')
        small++;
    }
    printf("大写字母为%d个，小写字母为%d个\n",big,small);
    return 0;
}
