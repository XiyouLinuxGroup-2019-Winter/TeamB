/*************************************************************************
	> File Name: pc.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月14日 星期四 21时14分09秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
typedef struct node{
    int date;
    struct node *next;
}Node;
typedef struct queue{
    Node *head;
    Node *tail;
    int num;
    int len;
}Queue;
Queue pc;
pthread_mutex_t mutex,mutex1,mutex2;
pthread_cond_t cond1,cond2;
int full(Queue *p)
{
    if(p->len==p->num){
        return 1;
    }
    else{
        return 0;
    }
}
int empty(Queue *p)
{
    if(p->len==0){
        return 1;
    }
    else{
        return 0;
    }
}
void create(Queue *p)
{
    p->num=10;
    p->head=NULL;
    p->tail=NULL;
    p->len=0;
}
int insert(Queue *p)
{
    Node *operate,*record;
    operate=(Node *)malloc(sizeof(Node));
    if(p->head==NULL){
        p->head=operate;
    }
    else{
        record=p->tail;
        record->next=operate;
    }
    operate->date=0;
    p->tail=operate;
    p->len++;
    return 0;
}
void rm(Queue *p)
{
    Node *operate=p->head;
    Node *record=operate->next;
    free(operate);
    p->head=record;
    p->len--;
}
void del(Queue *p)
{
    Node *operate,*record;
    operate=p->head;
    for(int i=0;i<p->len;i++){
        record=operate->next;
        free(operate);
        operate=record;
    }
}
void *producer(void *a)
{
    while(1){
        if(full(&pc)==0){
            pthread_mutex_lock(&mutex);
            insert(&pc);
            pthread_mutex_unlock(&mutex);
            printf("生产者生产一个,当前产品数为%d\n",pc.len);
            if(pc.len==1){
                pthread_cond_signal(&cond2);
            }
            sleep(1);
        }
        else{
            pthread_mutex_lock(&mutex1);
            printf("生产者挂起\n");
            pthread_cond_wait(&cond1,&mutex1);
            printf("生产者运行\n");
            pthread_mutex_unlock(&mutex1);
        }
    }
}
void *consumer(void *a)
{
    while(1){
        if(empty(&pc)==0){
            pthread_mutex_lock(&mutex);
            rm(&pc);
            pthread_mutex_unlock(&mutex);
            printf("消费者消费一个,当前产品数为%d\n",pc.len);
            if(pc.len==9){
                pthread_cond_signal(&cond1);
            }
            sleep(1);
        }
        else{
            pthread_mutex_lock(&mutex2);
            printf("消费者挂起\n");
            pthread_cond_wait(&cond2,&mutex2);
            printf("消费者运行\n");
            pthread_mutex_unlock(&mutex2);
        }
    }
}
int main()
{
    pthread_t th1,th2;
    pthread_mutex_init(&mutex1,NULL);
    pthread_cond_init(&cond1,NULL);
    pthread_mutex_init(&mutex2,NULL);
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond2,NULL);
    printf("生产者数目1\n消费者数目1\n");
    create(&pc);
    int ret=pthread_create(&th1,NULL,producer,NULL);
    if(ret!=0)
        printf("pthread_create produser error ");
    ret=pthread_create(&th2,NULL,consumer,NULL);
    if(ret!=0)
        printf("pthread_create consumer error ");
    sleep(20);
    del(&pc);
    printf("all over\n");
    exit(0);
}
