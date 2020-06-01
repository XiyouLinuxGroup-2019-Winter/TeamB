/*************************************************************************
	> File Name: pthread_QS.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月31日 星期日 21时13分01秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
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
    memset(sub.p,0x3f3f3f,sizeof(sub.p));
    int a[size];
    sub.len=size;
    for(int i=0;i<size;i++){
        scanf("%d",&a[i]);
    }
    int mid=a[size-1];
    sub.p[size-1]=mid;
    int j=1,k=1;
    for(int i=0;i<size;i++){
        if(a[i]>mid){
            sub.p[size-1+j]=a[i];
            j++;
        }
        else{
            sub.p[size-1-k]=a[i];
            k++;
        }
    }
    for(int i=0;i<size-1;i++){
        if(sub.p[i]==0x3f3f3f){
            sub.p=sub.p+1;
            free(&sub.p[i]);
        }
    }
    for(int i=0;i<size;i++){
        printf("%d ",sub.p[i]);
    }
}

