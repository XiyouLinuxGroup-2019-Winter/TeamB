/*************************************************************************
	> File Name: mutex.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月13日 星期三 21时31分38秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
pthread_mutex_t mutex;
void *thread1(void *a)
{
    int fd;
    fd=open("file",O_RDWR|O_CREAT|O_APPEND,0666);
    if(fd==-1){
        printf("18.open failed\n");
        exit(1);
    }
    pthread_cleanup_push(pthread_mutex_unlock,&mutex);
    pthread_cleanup_push(close,fd);
    int i=5;
    while(i>0){
        pthread_mutex_lock(&mutex);
        printf("thread1 get lock\n");
        i--;
        write(fd,"thread1 is writing\n",19);
        sleep(1);
        pthread_mutex_unlock(&mutex);
    }
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
}
void *thread2(void *a)
{
    int fd;
    fd=open("file",O_RDWR|O_CREAT|O_APPEND,0666);
    if(fd==-1){
        printf("18.open failed\n");
        exit(1);
    }
    pthread_cleanup_push(pthread_mutex_unlock,&mutex);
    pthread_cleanup_push(close,fd);
    int i=5;
    while(i>0){
        pthread_mutex_lock(&mutex);
        printf("thread2 get lock\n");
        i--;
        write(fd,"thread2 is writing\n",19);
        sleep(1);
        pthread_mutex_unlock(&mutex);
    }
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
}
int main()
{
    pthread_mutex_init(&mutex,NULL);
    pthread_t th1,th2;
    pthread_create(&th1,NULL,thread1,NULL);
    pthread_create(&th2,NULL,thread2,NULL);
    sleep(10);
    pthread_mutex_destroy(&mutex);
    return 0;
}
