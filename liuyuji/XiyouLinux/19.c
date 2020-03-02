/*************************************************************************
	> File Name: 19.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月28日 星期五 22时07分02秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void get_str(char **ptr)
{
    *ptr = (char*)malloc(17);
    strcpy(*ptr, "Xiyou Linux Group");
}
int main(int argc, char *argv[])
{
    char *str = NULL;
    get_str(&str);
    printf("%s\n", str);
}
