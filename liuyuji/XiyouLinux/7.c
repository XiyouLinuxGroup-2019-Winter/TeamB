/*************************************************************************
	> File Name: 7.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月01日 星期六 17时01分48秒
 ************************************************************************/

#include<stdio.h>
int f(unsigned int num);
int f(unsigned int num)
{ 
    unsigned int i;
    for (i = 0; num; i++) {
num &= (num - 1);
}
return i;
}
int main(){
    printf("%d",f((unsigned int)2018));
}
