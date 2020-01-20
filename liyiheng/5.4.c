#include<stdio.h>
int main()
{
    float cm,feet,inch;
    printf("Enter a height in centimeters:");
    scanf("%f",&cm);
    while(cm>0)
    {
        feet = cm * 0.0328084;
        inch = (int)feet % 12;
        printf("%.1fcm = %d feet,%.1f inches",cm,feet,inch);
        scanf("%f",&cm);
    }

}

