#include<stdio.h>
int main()
{
    float speed,bytes,time;
    printf("输入下载速度\n");
    scanf("%f",&speed);
    printf("输入文件大小\n");
    scanf("%f",&bytes);
    time = (bytes*8)/speed;
    printf("At %.2f megabits per second,a file of %.2f megabytes downloads in %.2f seconds\n",speed,bytes,time);
}
