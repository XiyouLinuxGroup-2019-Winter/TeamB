/*************************************************************************
	> File Name: bintree.h
	> Author: 
	> Mail: 
	> Created Time: 2020年03月25日 星期三 19时55分47秒
 ************************************************************************/

#ifndef _BINTREE_H
#define _BINTREE_H
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
typedef struct treenode{
    int date;
    struct node *left;
    struct node *right;
}Treenode;
typedef tree{
    Treenode *root;
    int Node_num;
}Tree;
void Init_tree(Tree *ptree);
bool Tree_empty(const Tree *ptree);
bool Tree_full(const Tree *ptree);
int Treenode_num(const Tree *ptree);
bool Add_node(Tree *ptree,int date);
bool Find_node(int date,Tree *ptree);
bool Del_node(int date,Tree *ptree);
void Del_tree(Tree *ptree);
#endif
