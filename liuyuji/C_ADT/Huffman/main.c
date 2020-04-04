/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月04日 星期六 15时56分21秒
 ************************************************************************/
#include "Huffman.h"
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
    printf("\n");
    free_heap(heap);
    free_huffman(H->root);
    free(H);
}
