#include<stdio.h>
#include<string.h>
int main()
{
  char a[20],b[20];
  int i = 0,j = 0;
    i=strlen(a);
    j=strlen(b);
    printf("请输入名和姓");
    scanf("%s %s",&a,&b);
    printf("\"%s %s\"\n",a,b);
    printf("\"%20s %20s\"\n",a,b);
    printf("\"%-20s %-20s\"\n",a,b);
    printf("%*s %*s\n",i,a,j,b); 
  return 0;

}

