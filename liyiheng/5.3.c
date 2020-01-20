#include<stdio.h>
int main(void)
{
    int day1,day2,week;
    scanf("%d",&day1);
    while(day1>0)
    {
        week = day1 / 7;
        day2 = day1 %7;
        printf("%d days are %d weeks,%d days",day1,week,day2);
        scanf("%d",&day1);
    }
}

