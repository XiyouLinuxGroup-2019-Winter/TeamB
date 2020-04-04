/*************************************************************************
	> File Name: huffman.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月31日 星期二 19时46分29秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
typedef struct huffmantree{
    int weight;
    struct huffmantree *left;
    struct huffmantree *right;
}Treenode;
typedef struct huffman{
    int Num;
    Treenode *root;
}Huffman;
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
    heap->Date=(Treenode **)malloc(sizeof(Treenode *)*(max+1));
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
    int num=++heap->Num;
    heap->Date[num]=node;
    while(num!=1 && heap->Date[num]->weight<heap->Date[num/2]->weight){
        Treenode *temp;
        temp=heap->Date[num/2];
        heap->Date[num/2]=heap->Date[num];
        heap->Date[num]=temp;
        num=num/2;
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
Huffman *creat_huffman(int num)
{
    Huffman *H=(Huffman *)malloc(sizeof(Huffman));
    H->Num=num;
    H->root=NULL;
    return H;
}
Treenode *Build_huffman(Heap *heap)//有bug
{
    Treenode *node;
    for(int i=1;i<heap->max;i++){
        node=(Treenode *)malloc(sizeof(Treenode));
        node->left=del(heap);
        node->right=del(heap);
        printf("第%d次合并%d,%d",i,node->left->weight,node->right->weight);
        node->weight=node->left->weight+node->right->weight;
        printf("成为%d\n",node->weight);
        insert(heap,node);
    }
    node=del(heap);
    return node;
}
void Display_huffman(Treenode *node)
{
    //中序遍历哈夫曼树
    if(node){
        Display_huffman(node->left);
        printf("%d ",node->weight);
        Display_huffman(node->right);
    }
}
void free_heap(Heap *heap)
{
    for(int i=0;i<heap->max;i++){
        free(heap->Date[i]);
    }
    free(heap->Date);
    free(heap);
}
void free_huffman(Treenode *node)
{
    if(node){
        free_huffman(node->left);
        free_huffman(node->right);
        free(node);
    }
}
int main()
{
    printf("请输入数据数量\n");
    int num;
    scanf("%d",&num);
    Heap *heap=creatheap(num);
    Huffman *H=creat_huffman(num);
    //将各数据的价值输入到最小堆中
    for(int i=1;i<=num;i++){
        printf("请输入第%d个数据的价值\n",i);
        int temp;
        scanf("%d",&temp);
        Treenode *node=(Treenode *)malloc(sizeof(Treenode));
        node->weight=temp;
        node->left=node->right=NULL;
        insert(heap,node);
    }
    H->root=Build_huffman(heap);
    printf("中序遍历哈夫曼树\n");
    Display_huffman(H->root);
    free_heap(heap);
    free_huffman(H->root);
    free(H);
}
