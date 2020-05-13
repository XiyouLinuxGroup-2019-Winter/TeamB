#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>


void *ftn(void *arg)
{
    while(1)
    {
        printf("thread:pid = %d,tid = %lu\n",getpid(),pthread_self());
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,ftn,NULL);

    if(ret != 0)
    {
        fprintf(stderr,"pthread_create error:%s\n",strerror(ret));
        exit(1);
    }

    printf("main:pid = %d,tid = %lu\n",getpid(),pthread_self());

    sleep(5);

    ret = pthread_cancel(tid);

    while(1)

    pthread_exit((void*)0);
}



