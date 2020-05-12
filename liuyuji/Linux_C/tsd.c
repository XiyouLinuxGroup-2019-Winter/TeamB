/*************************************************************************
	> File Name: tsd.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月12日 星期二 15时16分08秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<pthread.h>
pthread_key_t key;
void *thread1(void *a)
{
    int tsd=1;
    pthread_t th;
    th=pthread_self();
    pthread_setspecific(key,(void *)tsd);
    printf("thread1 id is %lu,return %d\n",th,pthread_getspecific(key));
    pthread_exit(NULL);
}
void *thread2(void *a)
{
    int tsd=2;
    pthread_t th;
    th=pthread_self();
    pthread_setspecific(key,(void *)tsd);
    printf("thread2 id is %lu,return %d\n",th,pthread_getspecific(key));
    pthread_exit(NULL);
}
int main()
{
    pthread_t th,th1,th2;
    th=pthread_self();
    pthread_key_create(&key,NULL);
    if((pthread_create(&th1,NULL,thread1,NULL))!=0){
        printf("24.thread1 create failed\n");
    }
    pthread_join(th1,NULL);
    printf("main id is %lu\n",th);
    if((pthread_create(&th2,NULL,thread2,NULL))!=0){
        printf("39.thread2 create failed\n");
    }
    pthread_join(th2,NULL);
    pthread_key_delete(key);
    return 0;
}
