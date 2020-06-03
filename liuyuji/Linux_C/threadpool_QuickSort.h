/*************************************************************************
	> File Name: threadpool_QuickSort.h
	> Author: 
	> Mail: 
	> Created Time: 2020年06月02日 星期二 22时46分22秒
 ************************************************************************/

#ifndef _THREADPOOL_QUICKSORT_H
#define _THREADPOOL_QUICKSORT_H

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
typedef struct work{
    void *(*fun)(int *a,int *arg);
    int *arg;
    struct work* next;
}Work;
typedef struct
{
    Work *queue_head;
    Work *queue_tail;
    int work_num;
    int max_work_num;

    pthread_t *thid;
    int thread_num;
    int max_thread_num;

    int shutdown;
}Thread_pool;
int *a;
Thread_pool *pool;
pthread_mutex_t mutex;
pthread_cond_t cond;
int full();
int add_work(void *(*fun)(int *a,int *arg),int *arg);
int del_work();
void *thread(void *a);
void pool_init(int max_thread_num);
void destroy_queue();
void pool_destroy();
void swap(int *a,int *b);
int Mid(int *a,int left,int right);
void *Quicksort(int *a,int *arg);
void Quick_Sort(int *a,int n);

#endif
