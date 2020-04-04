/*************************************************************************
	> File Name: Huffman.h
	> Author: 
	> Mail: 
	> Created Time: 2020年04月04日 星期六 15时54分11秒
 ************************************************************************/

#ifndef _HUFFMAN_H
#define _HUFFMAN_H

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
int empty(Heap *heap);
int full(Heap *heap);
Heap *creatheap(int max);
int insert(Heap *heap,Treenode *node);
Treenode *del(Heap *heap);
Huffman *creat_huffman(int num);
Treenode *Build_huffman(Heap *heap);
void Display_huffman(Treenode *node);
void free_heap(Heap *heap);
void free_huffman(Treenode *node);

#endif
