/*************************************************************************
	> File Name: pthread_self.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月11日 星期一 19时46分06秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

void *tfn(void *arg)
{
    printf("pthread:pid = %d,tid = %lu\n",getpid(),pthread_self());
    return NULL;
}


int main()
{
    pthread_t tid;
    
    printf("main:pid = %d,tid = %lu\n",getpid(),pthread_self());

    int ret;

    ret = pthread_create(&tid,NULL,tfn,NULL);
    if(ret != 0)
    {
        perror("error\n");
    }
    
    pthread_exit((void *)0);
}
