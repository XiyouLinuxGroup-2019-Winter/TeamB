#include<stdio.h>
#define h 60
int main()
{
    int min,hour,min2;
    printf("请输入时间");
    scanf("%d",&min);
    while(min>0)
    {
        if(min<=h)
        printf("%d",min);
        else 
        hour=min/h;
        min2=min%h;
        printf("%2d:%2d\n",hour,min2);
        scanf("%d",&min);

    }
}

