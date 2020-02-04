/*************************************************************************
	> File Name: 18.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月03日 星期一 16时18分23秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[])
{
int t = 4;
printf("%lu\n", sizeof(t--));
printf("%lu\n", sizeof("ab c\nt\012\xa1*2"));
printf("%d\n",t);
printf("%s\n","ab c\nt\101\x41*2");
return 0;
}
