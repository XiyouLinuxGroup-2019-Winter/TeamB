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
Huffman *creat_huffman(int num)
{
    Huffman *H=(Huffman *)malloc(sizeof(Huffman));
    H->Num=num;
    H->root=NULL;
    return H;
}
Treenode *Build_huffman(Heap *heap)
{
    Treenode *node;
    for(int i=0;i<heap->Num;i++){
        node=(Treenode *)malloc(sizeof(Treenode));
        node->left=del(heap);
        node->right=del(heap);
        node->weight=node->left->weight+node->left->weight;
        insert(heap,node);
    }
    node=del(heap);
    return node;
}
void Display_huffman(Huffman *H,Treenode *node)
{
    //中序遍历哈夫曼树
    if(node){
        Display_huffman(H,node->left);
        printf("%d ",node->weight);
        Display_huffman(H,node->right);
    }
}
void free_heap(Heap *heap)
{
    for(int i=0;i<heap->Num;i++){
        free(heap->Date[i]);
    }
    free(heap->Date);
    free(heap);
}
void free_huffman(Huffman *H,Treenode *node)
{
    if(node){
        free_huffman(H,node->left);
        free_huffman(H,node->right);
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
        insert(heap,node);
    }
    Build_huffman(heap);
    Display_huffman(H,H->root);
    free_heap(heap);
    free_huffman(H,H->root);
    free(H);
}
