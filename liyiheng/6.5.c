#include<stdio.h>
#include<string.h>
int main()
{
  char a[50];
    int i;
    while(scanf("%s",a)==1)
    {
        for(i=strlen(a)-1;i>=0;i--)
        printf("%c",a[i]);
        printf("\n");
    }
    return 0;
}
