/*************************************************************************
	> File Name: cond.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月13日 星期三 22时23分19秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
pthread_mutex_t mutex;
pthread_cond_t cond;
void *thread1(void *a)
{
    pthread_cleanup_push(pthread_mutex_unlock,&mutex);
    while(1){
        printf("thread1 is runing\n");
        pthread_mutex_lock(&mutex);
        printf("thread1 get mutex\n");
        pthread_cond_wait(&cond,&mutex);
        printf("thread1 get cond\n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_cleanup_pop(0);
}
void *thread2(void *a)
{
    pthread_cleanup_push(pthread_mutex_unlock,&mutex);
    while(1){
        printf("thread2 is runing\n");
        pthread_mutex_lock(&mutex);
        printf("thread2 get mutex\n");
        pthread_cond_wait(&cond,&mutex);
        printf("thread2 get cond\n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_cleanup_pop(0);
}
int main()
{
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_t th1,th2;
    pthread_create(&th1,NULL,thread1,NULL);
    pthread_create(&th2,NULL,thread2,NULL);
    for(int i=0;i<=30;i++){
        if(i%5==0){
            pthread_cond_signal(&cond);
            printf("i=%d\n",i);
            sleep(1);
        }
    }
    printf("main exit\n");
    exit(0);
}
