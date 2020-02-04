/*************************************************************************
	> File Name: 5.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月01日 星期六 14时29分12秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char *argv[])
{
int a[3][2] = { 2, 0, 1, 8 };
char *str = (char *)malloc(sizeof(char) * 20);
strcpy(str, "\0101\\xb2");
printf("%zu\n", sizeof(a));
printf("%zu %d\n", sizeof(a[1][1] =0), a[1][1]); //4. 下面是一个 C 语言程序从源代码到形成可执行文件的过程,请解释图
printf("%zu %zu\n", sizeof(str), strlen(str));// 中的 ABCD 分别表示什么,在每个阶段分别完成了什么工作?
return 0;
}
