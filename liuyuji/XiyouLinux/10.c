/*************************************************************************
	> File Name: 10.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月02日 星期日 21时15分53秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
size_t q(size_t b)
{
return b;
}
size_t (*p(char *str))(size_t a)
{
printf("%s\n", str);
return q;
}
int main(int argc, char *argv[])
{
char str[] = "XiyouLinuxGroup";
printf("%lu\n", p(str)(strlen(str)));
return 0;
}
