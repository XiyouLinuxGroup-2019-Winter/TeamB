/*************************************************************************
	> File Name: 13.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月02日 星期日 21时43分22秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[])
{
char str[512];
int i;
for (i = 0; i < 512; ++i)
{
		
str[i] = -1 - i;
}
printf("%lu\n", strlen(str));
return 0;
}
