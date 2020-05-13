#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

struct thrd{
    int var;
    char str[256];
};

void *tfn(void *arg)
{
    struct thrd* tval;
    tval = malloc(sizeof(tval));
    tval->var = 100;
    strcpy(tval-> str , "hello world");
    return (void *)tval;
}

int main()
{
    pthread_t tid;
    int ret;
    struct thrd *retval;

    ret = pthread_create(&tid,NULL,tfn,NULL);
    if(ret != 0)
    {
        perror("pthread_creat error\n");
    }


    pthread_join(tid,(void**)&retval);


    printf("child thread var = %d,str = %s\n",retval -> var,retval -> str);

    pthread_exit(NULL);

}




