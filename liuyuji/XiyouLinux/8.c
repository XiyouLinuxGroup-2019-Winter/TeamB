/*************************************************************************
	> File Name: 8.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月02日 星期日 20时33分49秒
 ************************************************************************/

#include<stdio.h>
int main(int argc, char *argv[])
{
int t = 4;
printf("%lu\n", sizeof(t--));
printf("%lu\n", sizeof("ab c\nt\012\xa1*2"));
return 0;
}
