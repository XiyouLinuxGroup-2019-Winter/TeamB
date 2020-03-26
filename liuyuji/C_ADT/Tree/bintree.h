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
    struct treenode *left;
    struct treenode *right;
}Treenode;
typedef struct {
    Treenode *root;
    int Node_num;
}Tree;
void Init_tree(Tree *ptree);
int Tree_empty(const Tree *ptree);
int Tree_full(const Tree *ptree);
int Treenode_num(const Tree *ptree);
int Add_node(int date,Tree *ptree);
int Find_node(int date,Treenode *operate,Treenode **record,Treenode **parent);
int Del_node(int date,Tree *ptree);
void Del_tree(Tree *ptree);
void Display_tree(const Treenode *operate);
#endif
