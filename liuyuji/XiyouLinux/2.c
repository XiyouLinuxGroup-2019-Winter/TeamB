/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月31日 星期五 15时51分23秒
 ************************************************************************/

#include<stdio.h>
int main(int argc, char *argv[]) {
char x = -2, y = 3;
char t = (++x) | (y++);
printf("x = %d, y = %d, t = %d\n", x, y, t);
t = (++x) || (y++);
printf("x = %d, y = %d, t = %d\n", x, y, t);}
