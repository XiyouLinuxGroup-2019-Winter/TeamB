#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<errno.h>


void err_thread(int ret,char* str)
{
    if(ret != 0)
    {
        fprintf(stderr,"%s:%s\n",str,strerror(ret));
        pthread_exit(NULL);
    }
}

struct msg{
    int num;
    struct msg* next;
};



struct msg* head;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//定义并初始化互斥锁
pthread_cond_t has_data = PTHREAD_COND_INITIALIZER;//定义并初始化条件变量



void* produster(void* arg)
{
    while(1){

       struct msg* mp = (struct msg*)malloc(sizeof(struct msg));
       mp -> num = rand()%1000 + 1;//模拟生产一个数据

       printf("---produster is %d\n",mp -> num);
       pthread_mutex_lock(&mutex);//加锁

       mp -> next = head;
       head = mp;//写公共区域

       pthread_mutex_unlock(&mutex);
       pthread_cond_signal(&has_data);
       sleep(rand()%3); 
    }
    return  NULL;
}


void* consumer(void* arg)
{
    while(1){
       struct msg* mp;
       pthread_mutex_lock(&mutex);//加锁
       while(head == NULL)
      {
        pthread_cond_wait(&has_data,&mutex);//阻塞等待条件变量，解锁，pthread_cond_wait返回时重新加锁
      }
    
       mp = head;
       head = mp -> next;

       pthread_mutex_unlock(&mutex);

       printf("consumer is %d,ID is %lu\n",mp -> num,pthread_self());

       free(mp);

       sleep(rand()%3);
    }

     return NULL;
}


int main()
{
    pthread_t pid,cid;
    int ret;
    
    srand(time(NULL));


    ret = pthread_create(&pid,NULL,produster,NULL);//创建生产者线程
    if(ret != 0)
    {
        err_thread(ret,"pthread_create produster error");
    }


    ret = pthread_create(&cid,NULL,consumer,NULL);//创建消费者者线程
    if(ret != 0)
    err_thread(ret,"pthread_create consumer error");
       

    ret = pthread_create(&cid,NULL,consumer,NULL);//创建消费者者线程
    if(ret != 0)
    err_thread(ret,"pthread_create consumer error");


    ret = pthread_create(&cid,NULL,consumer,NULL);//创建消费者者线程
    if(ret != 0)
    err_thread(ret,"pthread_create consumer error");


    pthread_join(pid,NULL);
    pthread_join(cid,NULL);
}

