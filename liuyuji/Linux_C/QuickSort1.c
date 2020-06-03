/*************************************************************************
	> File Name: pthread_QS.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月31日 星期日 21时13分01秒
 ************************************************************************/

#include"threadpool_QuickSort.h"
int full()
{
    if(pool->work_num==pool->max_work_num){
        return 1;
    }
    else{
        return 0;
    }
}
int add_work(void *(*fun)(int *a,int *arg),int *arg)
{
    if(full()==1){
        printf("work queue is full\n");
        return 0;
    }
    Work *operate,*record;
    operate=(Work *)malloc(sizeof(Work));
    operate->fun=fun;
    operate->arg=arg;
    operate->next=NULL;
    
    pthread_mutex_lock(&mutex);
    pool->work_num++;
    if(pool->queue_head==NULL){
        pool->queue_head=operate;
        pool->queue_tail=operate;
    }
    else{
        record=pool->queue_tail;
        record->next=operate;
        pool->queue_tail=operate;
    }
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond);
}
int del_work()
{
    Work *operate=pool->queue_head;
    pool->queue_head=operate->next;
    if(pool->queue_head==NULL){
        pool->queue_tail=NULL;
    }
    free(operate);
    pool->work_num--;
}
void *thread(void *arg)
{
    while(1){
        pthread_mutex_lock(&mutex);
        while (pool->work_num == 0 && !pool->shutdown)
        {
            printf ("thread %ld is waiting\n", pthread_self ());
            pthread_cond_wait(&cond,&mutex);
        }
        if(pool->shutdown==1){
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        printf("thread %ld is working\n",pthread_self());
        Work *operate=pool->queue_head;
        del_work();
        pthread_mutex_unlock(&mutex);
        Quicksort(a,operate->arg);
    }
}
void pool_init(int max_thread_num)
{
    pthread_cond_init(&cond,NULL);
    pthread_mutex_init(&mutex,NULL);

    pool=(Thread_pool *)malloc(sizeof(Thread_pool));

    pool->queue_head=NULL;
    pool->queue_tail=NULL;
    pool->work_num=0;
    pool->max_work_num=20;

    pool->thid=(pthread_t *)malloc(10 * sizeof(pthread_t));
    memset(pool->thid,0,10 * sizeof(pthread_t));
    pool->thread_num=max_thread_num;
    pool->max_thread_num=10;

    pool->shutdown=0;
    
    for(int i=0;i<max_thread_num;i++){
        pthread_create(&pool->thid[i],NULL,thread,NULL);
    }
}
void destroy_queue()
{
    Work *operate,*record;
    operate=pool->queue_head;
    while(operate){
        record=operate->next;
        free(operate);
        operate=record;
    }
}
void pool_destroy()
{
    int i=0;
    pool->shutdown=1;
    pthread_cond_broadcast(&cond);
    for(int i=0;i<pool->thread_num;i++){
        pthread_join(pool->thid[i],NULL);
    }
    free(pool->thid);
    destroy_queue();
    free(pool);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}
void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
int Mid(int *a,int left,int right)
{
    int size;
    size=(left+right)/2;
    if(a[left]>a[size]){
        swap(&a[left],&a[size]);
    }
    if(a[left]>a[right]){
        swap(&a[left],&a[right]);
    }
    if(a[size]>a[right]){
        swap(&a[right],&a[size]);
    }
    swap(&a[size],&a[right-1]);
    return a[right-1];
}
void *Quicksort(int *a,int *arg)
{
    int left,right;
    left=arg[0];
    right=arg[1];
//    if(right-left+1<2){
//        return NULL;
//    }
//    if(MIDNUM<right-left+1){
        int mid=Mid(a,left,right);
        int i=left,j=right-1;
        while(1){
            while(a[++i]<mid);
            while(a[--j]>mid);
            if(i<j){
                swap(&a[i],&a[j]);
            }
            else{
                break;
            }
        }
        swap(&a[i],&a[right-1]);
        int *left_sub=(int *)malloc(2*sizeof(int));
        int *right_sub=(int *)malloc(2*sizeof(int));
        left_sub[0]=left;
        left_sub[1]=i-1;
        right_sub[0]=i+1;
        right_sub[1]=right;
        if(i-left>1)add_work(Quicksort,left_sub);
        if(right-i>1)add_work(Quicksort,right_sub);
//    else{
//
//    }
}
void Quick_Sort(int *a,int n)
{
    int *num=(int *)malloc(8);
    num[0]=0;
    num[1]=n-1;
    add_work(Quicksort,num);
}
int main()
{
    pool_init(6);
    int size;
    scanf("%d",&size);
    a=(int *)malloc(size*sizeof(int));
    for(int i=0;i<size;i++){
        scanf("%d",&a[i]);
    }
    Quick_Sort(a,size);
    sleep(10);
    for(int i=0;i<size;i++){
        printf("%d ",a[i]);
    }
    pool_destroy();
    free(a);
    return 0;
}

