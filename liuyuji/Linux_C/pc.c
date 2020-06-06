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
pthread_mutex_t mutex;
pthread_cond_t cond,cond1;
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
    p->num=5;
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
    operate->date=rand()%50;
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
        pthread_mutex_lock(&mutex);
        while(full(&pc)==1){
            printf("生产者%ld等待中\n",pthread_self());
            pthread_cond_wait(&cond,&mutex);
        }
        insert(&pc);
        printf("生产者%ld生产%d\n",pthread_self(),pc.tail->date);
        if(pc.len==1){
            pthread_cond_signal(&cond);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}
void *consumer(void *a)
{
    while(1){
        pthread_mutex_lock(&mutex);
        while(empty(&pc)==1){
            printf("\t\t\t消费者%ld等待中\n",pthread_self());
            pthread_cond_wait(&cond,&mutex);
        }
        printf("\t\t\t消费者%ld消费%d\n",pthread_self(),pc.head->date);
        rm(&pc);
        if(pc.len==5){
            pthread_cond_signal(&cond1);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}
int main()
{
    pthread_t th1,th2,th3,th4,th5,th6;
    pthread_cond_init(&cond,NULL);
    pthread_cond_init(&cond1,NULL);
    pthread_mutex_init(&mutex,NULL);
    create(&pc);
    int ret;
    ret=pthread_create(&th1,NULL,producer,NULL);
    if(ret!=0)
        printf("pthread_create produser error ");
    ret=pthread_create(&th2,NULL,producer,NULL);
    if(ret!=0)
        printf("pthread_create produser error ");
    ret=pthread_create(&th3,NULL,producer,NULL);
    if(ret!=0)
        printf("pthread_create produser error ");
    ret=pthread_create(&th4,NULL,consumer,NULL);
    if(ret!=0)
        printf("pthread_create consumer error ");
    ret=pthread_create(&th5,NULL,consumer,NULL);
    if(ret!=0)
        printf("pthread_create consumer error ");
    ret=pthread_create(&th6,NULL,consumer,NULL);
    if(ret!=0)
        printf("pthread_create consumer error ");
    pthread_cond_broadcast(&cond);
    sleep(10);
    del(&pc);
    printf("all over\n");
    exit(0);
}
