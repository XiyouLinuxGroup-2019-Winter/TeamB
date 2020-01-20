#include<stdio.h>
#include<string.h>
int main()
{
    char a[20],b[20];
    int i=0,j=0;
    printf("请先输入名，再输入姓\n");
    scanf("%s %s",&a,&b);
    i=strlen(a);
    j=strlen(b);
    printf("%s %s\n",a,b);
    printf("%*d %*d\n",i,j);
    printf("%s %s\n",a,b);
    printf("%-*d %-*d\n",i,j);
    return 0;
}
