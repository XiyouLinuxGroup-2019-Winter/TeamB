/*************************************************************************
	> File Name: pthread_QS.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月31日 星期日 21时13分01秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<pthread.h>
typedef struct list{
    int *p;
    int len;
}List;
List sub;
void *thread(void *a)
{

}
int main()
{
    int size;
    scanf("%d",&size);
    sub.p=(int *)malloc(size*sizeof(int));
    sub.len=size;
    for(int i=0;i<size;i++){
        scanf("%d",sub.p[i]);
    }
    int mid=sub.len/2;

}

