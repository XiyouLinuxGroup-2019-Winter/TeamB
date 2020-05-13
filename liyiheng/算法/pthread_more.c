#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

void *tfn(void *arg)
{
    int i = (int)arg;
    sleep(i);
    if(i == 2)
    {
        pthread_exit(NULL);
    }
    printf("I am %dth pthread,pid = %d,tid = %lu\n",i+1,getpid(),pthread_self());
    return NULL;
}


int main()
{
    pthread_t tid;
    int ret;
    int i = 0;
    for(i;i < 5;i++)
    {
       ret = pthread_create(&tid,NULL,tfn,(void*)i);
       if(ret != 0)
        {
          perror("error\n");
        }
    }
    sleep(i);
    printf("I am main,pid = %d,tid = %lu\n",getpid(),pthread_self());
    return 0;
}
