/*************************************************************************
	> File Name: Minheap.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月01日 星期三 20时16分40秒
 ************************************************************************/

#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct heaphead{
    Treenode **Date;
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
    heap->Date=(Treenode *)malloc(sizeof(Treenode)*(max+1));
    if(heap==NULL){
        printf("malloc %d",__LINE__);
        exit(1);
    }
    heap->Num=0;
    heap->Date[0]=NULL;
    heap->max=max;
    return heap;
}
int insert(Heap *heap,Treenode *node)
{
    if(full(heap)==1){
        printf("输入失败堆已满\n");
        return 0;
    }
    int num=heap->Num++;
    heap->Date[++num]=node;
    if(num==1){
        return 0;
    }
    while(heap->Date[num]->weight<heap->Date[num/2]->weight){
        Treenode *temp;
        temp=heap->Date[num/2];
        heap->Date[num/2]=heap->Date[num];
        heap->Date[num]=temp;
        num/=2;
        if(num==1){
            break;
        }
    }
}
Treenode *del(Heap *heap)
{
    if(empty(heap)==1){
        printf("堆为空\n");
        return 0;
    }
    Treenode *Mindate=heap->Date[1];
    Treenode *temp=heap->Date[heap->Num--];
    int parent,child;
    for( parent=1; parent*2<=heap->Num; parent=child){
        child=parent*2;
        if((child!=heap->Num) && (heap->Date[child]->weight>heap->Date[child+1]->weight)){
            child++;
        }
        if(temp->weight<=heap->Date[child]->weight){
            break;
        }
        else{
            heap->Date[parent]=heap->Date[child];
        }
    }
    heap->Date[parent]=temp;
    return Mindate;
}
