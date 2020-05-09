/*************************************************************************
	> File Name: join.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月09日 星期六 21时15分29秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
void pth(void *arg)
{
    printf("th\n");
    sleep(3);
    pthread_exit(0);
}
int main()
{
    pthread_t th;
    int status;
    pthread_create(&th,NULL,(void *)pth,NULL);
    pthread_join(th,(void *)&status);
    printf("%d\n",status);
    return 0;
}
