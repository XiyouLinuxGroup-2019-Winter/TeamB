/*************************************************************************
	> File Name: 3.c
	> Author: 
	> Mail: 
	> Created Time: 2020年01月31日 星期五 16时03分47秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]) {
char *p = (char *)malloc(sizeof(char) * 20),
*q = p;
scanf("%s %s", p, q);
printf("%s %s\n", p, q);
}
