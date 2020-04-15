/*************************************************************************
	> File Name: my_signal.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月10日 星期五 22时00分17秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
void handler(int signo)
{
    printf("recv SIGINT\n");
}
int main()
{
    signal(SIGINT,handler);
    while(1)
        ;
    return 0;
}
