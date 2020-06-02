/*************************************************************************
	> File Name: pthread_QS.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月31日 星期日 21时13分01秒
 ************************************************************************/

#include"threadpool_QuickSort.h"
int *a;
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
        int temp=a[left];
        a[left]=a[size];
        a[size]=temp;
    }
    if(a[left]>a[right]){
        int temp=a[left];
        a[left]=a[right];
        a[right]=temp;
    }
    if(a[size]>a[right]){
        int temp=a[size];
        a[size]=a[right];
        a[right]=temp;
    }
    swap(&a[size],&a[right-1]);
    return a[right-1];
}
void *Quicksort(int *a,int *arg)
{
    int left,right;
    left=arg[0];
    right=arg[1];
    if(right-left+1<2){
        return NULL;
    }
//    if(MIDNUM<right-left+1){
        int mid=Mid(a,left,right);
        int i=left,j=right-1;
        while(1){
            while(a[++i]>mid);
            while(a[--j]<mid);
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
        add_work(Quicksort,left_sub);
        add_work(Quicksort,right_sub);
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
    for(int i=0;i<size;i++){
        printf("%d ",a[i]);
    }
    pool_destroy();
    free(a);
    return 0;
}

