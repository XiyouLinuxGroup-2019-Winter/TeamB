/*************************************************************************
	> File Name: zxj.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月21日 星期四 20时22分38秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
pthread_mutex_t mutex,mutex1,mutex2,mutex3,mutex4,mutex5;
pthread_cond_t cond;
int num=4;
void* th1(void *a)
{
    while(1){
        if(num<1){
            pthread_mutex_lock(&mutex);
            pthread_cond_wait(&cond,&mutex);
            pthread_mutex_unlock(&mutex);
        }
        pthread_mutex_lock(&mutex1);
        num--;
        printf("1号拿到左边的筷子1\n");
        pthread_mutex_lock(&mutex5);
        printf("1号拿到右边的筷子5\n1号开始吃饭\n");
        sleep(1);
        printf("1号吃完放下筷子\n");
        pthread_mutex_unlock(&mutex1);
        pthread_mutex_unlock(&mutex5);
        num++;
        pthread_cond_signal(&cond);
        pthread_exit(NULL);
    }
}
void* th2(void *a)
{
    while(1){
        if(num<1){
            pthread_mutex_lock(&mutex);
            pthread_cond_wait(&cond,&mutex);
            pthread_mutex_unlock(&mutex);
        }
        pthread_mutex_lock(&mutex2);
        num--;
        printf("2号拿到左边的筷子2\n");
        pthread_mutex_lock(&mutex1);
        printf("2号拿到右边的筷子1\n2号开始吃饭\n");
        sleep(1);
        printf("2号吃完放下筷子\n");
        pthread_mutex_unlock(&mutex2);
        pthread_mutex_unlock(&mutex1);
        num++;
        pthread_cond_signal(&cond);
        pthread_exit(NULL);
    }
}
void* th3(void *a)
{
    while(1){
        if(num<1){
            pthread_mutex_lock(&mutex);
            pthread_cond_wait(&cond,&mutex);
            pthread_mutex_unlock(&mutex);
        }
        pthread_mutex_lock(&mutex3);
        num--;
        printf("3号拿到左边的筷子3\n");
        pthread_mutex_lock(&mutex2);
        printf("3号拿到右边的筷子2\n3号开始吃饭\n");
        sleep(1);
        printf("3号吃完放下筷子\n");
        pthread_mutex_unlock(&mutex3);
        pthread_mutex_unlock(&mutex2);
        num++;
        pthread_cond_signal(&cond);
        pthread_exit(NULL);
    }
}
void* th4(void *a)
{
    while(1){
        if(num<1){
            pthread_mutex_lock(&mutex);
            pthread_cond_wait(&cond,&mutex);
            pthread_mutex_unlock(&mutex);
        }
        pthread_mutex_lock(&mutex4);
        num--;
        printf("4号拿到左边的筷子4\n");
        pthread_mutex_lock(&mutex3);
        printf("4号拿到右边的筷子3\n4号开始吃饭\n");
        sleep(1);
        printf("4号吃完放下筷子\n");
        pthread_mutex_unlock(&mutex4);
        pthread_mutex_unlock(&mutex3);
        num++;
        pthread_cond_signal(&cond);
        pthread_exit(NULL);
    }
}
void* th5(void *a)
{
    while(1){
        if(num<1){
            pthread_mutex_lock(&mutex);
            pthread_cond_wait(&cond,&mutex);
            pthread_mutex_unlock(&mutex);
        }
        pthread_mutex_lock(&mutex5);
        num--;
        printf("5号拿到左边的筷子5\n");
        pthread_mutex_lock(&mutex4);
        printf("5号拿到右边的筷子4\n5号开始吃饭\n");
        sleep(1);
        printf("5号吃完放下筷子\n");
        pthread_mutex_unlock(&mutex5);
        pthread_mutex_unlock(&mutex4);
        num++;
        pthread_cond_signal(&cond);
        pthread_exit(NULL);
    }
}
int main()
{
    pthread_cond_init(&cond,NULL);
    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_init(&mutex1,NULL);
    pthread_mutex_init(&mutex2,NULL);
    pthread_mutex_init(&mutex3,NULL);
    pthread_mutex_init(&mutex4,NULL);
    pthread_mutex_init(&mutex5,NULL);
    pthread_t thid[5];
    pthread_create(&thid[0],NULL,th1,NULL);
    pthread_create(&thid[1],NULL,th2,NULL);
    pthread_create(&thid[2],NULL,th3,NULL);
    pthread_create(&thid[3],NULL,th4,NULL);
    pthread_create(&thid[4],NULL,th5,NULL);
    pthread_join(thid[0],NULL);
    pthread_join(thid[1],NULL);
    pthread_join(thid[2],NULL);
    pthread_join(thid[3],NULL);
    pthread_join(thid[4],NULL);
    pthread_cond_destroy(&cond);
    exit(0);
}
