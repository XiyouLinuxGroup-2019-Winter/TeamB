/*************************************************************************
	> File Name: test_select.c
	> Author: 
	> Mail: 
	> Created Time: 2020年06月08日 星期一 20时19分59秒
 ************************************************************************/

#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
void dispaly_time(const char* str)
{
    int seconds;
    seconds=time((time_t*)NULL);
    printf("%s,%d\n",str,seconds);
}
int main()
{
    fd_set readfds;
    int ret;
    struct timeval time;
    time.tv_sec=5;
    time.tv_usec=0;
    FD_ZERO(&readfds);
    FD_SET(0,&readfds);
    while(1){
        dispaly_time("before select");
        ret=select(1,&readfds,NULL,NULL,&time);
        dispaly_time("after select");
        switch(ret){
            case 0:
            printf("no change\n");
            break;
            case -1:
            perror("select");
            exit(1);
            break;
            default:
            getchar();
            printf("have data\n");
        }
    }
    return 0;
}
