/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月09日 星期一 17时16分43秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main()
{
    char a[10]="/home";
    a[strlen(a)]='/';
    printf("%ld",strlen(a));
}
