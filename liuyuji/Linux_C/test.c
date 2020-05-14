/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月14日 星期四 16时44分51秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
void* thread1(void *a){
    printf("thread1 is running\n");
    pthread_exit(0);
}
void* thread2(void *a){
    printf("thread2 is running\n");
    pthread_exit(0);
}
void* thread3(void *a){
    printf("thread3 is running\n");
    pthread_exit(0);
}
void* thread4(void *a){
    printf("thread4 is running\n");
    pthread_exit(0);
}
int main()
{
    pid_t pid;
    pthread_t th1,th2,th3,th4;
    pid=fork();
    switch(pid){
        case 0:
        printf("This is child,pid is %d\n",getpid());
        pthread_create(&th1,NULL,thread1,NULL);
        pthread_join(th1,NULL);
        printf("thread1 have exited\n");
        pthread_create(&th2,NULL,thread2,NULL);
        pthread_join(th2,NULL);
        printf("thread2 have exited\n");
        break;
        default:
        wait(NULL);
        printf("This is parent,pid is %d\n",getpid());
        pthread_create(&th3,NULL,thread3,NULL);
        pthread_join(th3,NULL);
        printf("thread3 have exited\n");
        pthread_create(&th4,NULL,thread4,NULL);
        pthread_join(th4,NULL);
        printf("thread4 have exited\n");
        break;
    }
    if(pid==0)printf("child process exit\n");
    else{
        printf("parent process exit\n");
    }
    exit(0);
}
