/*************************************************************************
	> File Name: Maxheap.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月28日 星期六 21时49分10秒
 ************************************************************************/
//最大堆
#include<stdio.h>
#include<stdlib.h>
typedef heap{
    int *date;
    int num;
    int max;
}Heap;
int main()
{
    int num;
    printf("输入堆的大小\n");
    scanf("%d",&num);
    creat(num);
}
Heap *creat(int max)
