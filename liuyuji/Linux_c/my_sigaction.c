/*************************************************************************
	> File Name: my_sigaction.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月11日 星期六 20时45分38秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
int temp=0;
void hamdler_sigint(int signo)
{
    printf("recv SIGINT\n");
    sleep(5);
    temp++;
    printf("%d",temp);
}
int main()
{
    struct sigaction act;
    act.sa_handler=hamdler_sigint;
    act.sa_flags=SA_NOMASK;
    sigaction(SIGINT,&act,NULL);
    while(1)
        ;
    return 0;
}
