/*************************************************************************
	> File Name: createthread.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月08日 星期五 21时31分42秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
void* thread(void* a){
    pthread_t newthid;
    newthid=pthread_self();
    printf("newthid is %lu\n",newthid);
    return NULL;
}
int main()
{
    pthread_t thid,thid2;
    thid=pthread_self();
    printf("main thread id is %lu\n",thid);
    if(pthread_create(&thid2,NULL,thread,NULL)!=0){
        printf("create new thread faild\n");
        exit(1);
    }
    sleep(1);
    exit(0);
}
