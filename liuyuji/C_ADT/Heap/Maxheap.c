/*************************************************************************
	> File Name: Maxheap.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月28日 星期六 21时49分10秒
 ************************************************************************/
//最大堆
#include<stdio.h>
#include<stdlib.h>
typedef struct heaphead{
    int *Date;
    int Num;
    int max;
}Heap;
int empty(Heap *heap)
{
    if(heap->Num==0){
        return 1;
    }
    else{
        return 0;
    }
}
int full(Heap *heap)
{
    if(heap->Num==heap->max){
        return 1;
    }
    else{
        return 0;
    }
}
Heap *creatheap(int max)
{
    Heap *heap=(Heap *)malloc(sizeof(Heap));
    heap->Date=(int *)malloc(sizeof(int)*(max+1));
    if(heap==NULL){
        printf("malloc %d",__LINE__);
        exit(1);
    }
    heap->Num=0;
    heap->Date[0]=0x3f3f3f3f;
    heap->max=max;
    return heap;
}
int insert(Heap *heap,int date)
{
    if(full(heap)==1){
        printf("输入失败堆已满\n");
        return 0;
    }
    int num=heap->Num++;
    heap->Date[++num]=date;
    if(num==1){
        return 0;
    }
    while(heap->Date[num]>heap->Date[num/2]){
        int temp;
        temp=heap->Date[num/2];
        heap->Date[num/2]=heap->Date[num];
        heap->Date[num]=temp;
        num/=2;
        if(num==1){
            break;
        }
    }
}
int del(Heap *heap)
{
    if(empty(heap)==1){
        printf("堆为空\n");
        return 0;
    }
    int Maxdate=heap->Date[1];
    int temp=heap->Date[heap->Num--];
    int parent,child;
    for( parent=1; parent*2<=heap->Num; parent=child){
        child=parent*2;
        if((child!=heap->Num) && (heap->Date[child]<heap->Date[child+1])){
            child++;
        }
        if(temp>=heap->Date[child]){
            break;
        }
        else{
            heap->Date[parent]=heap->Date[child];
        }
    }
    heap->Date[parent]=temp;
    return Maxdate;
}
int main(char argc,char **argv)
{
    int max,date;
    printf("输入堆的大小\n");
    scanf("%d",&max);
    Heap *heap=creatheap(max);
    while(1){
        printf("1.入堆\n2.出堆\n3.退出\n");
        int chose;
        scanf("%d",&chose);
        switch(chose){
            case 1:
                printf("输入数据\n");
                scanf("%d",&date);
                insert(heap,date);
                break;
            case 2:
                date=del(heap);
            if(date!=0){
                printf("%d\n",date);
            }
                break;
            case 3:
                free(heap->Date);
                free(heap);
                exit(0);
        }
    }
}
