#include<stdio.h>
int main()
{
    float h;
    char name[10];
    printf("请输入身高和姓名");
    scanf("%f",&h);
    scanf("%s",&name);
    printf("%s,you are %f feet tall\n",name,h);
}

