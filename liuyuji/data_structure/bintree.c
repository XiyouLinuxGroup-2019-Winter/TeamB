/*************************************************************************
	> File Name: bintree.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月24日 星期二 21时39分17秒
 ************************************************************************/
//动态创建二叉查找树
#include<stdio.h>
#include"bintree.h"
typedef struct treenode{
    int date;
    struct node *left;
    struct node *right;
}Treenode;
typedef {
    Treenode *root;
    int Node_num;
}Tree;
#define LEFT 1
#define RIGHT 2
int main()
{
    Tree tree;
    Init_tree(&tree);
    while(1){
        printf("1.添加节点\n2.删除节点\n3.查找节点\n4.遍历二叉树\n5.清空退出\n");
        int chose;
        scanf("%d",&chose);
        if(chose==1){
            printf("请输入数据\n");
            int date;
            scanf("%d",&date);
            if((Add_node(date,&tree))==1){
                printf("添加成功\n");
            }
        }else if(chose==2){
            printf("请输入要删除的数据\n");
            int date;
            scanf("%d",&date);
            if((Del_node(date,&tree))==1){
                printf("删除成功\n");
            }
        }else if(chose==3){
            printf("请输入要查找的数据\n");
            int date;
            scanf("%d",&date);
            Find_node(date,&tree);
        }else if(chose==4){
            Display_tree(&tree);
        }else if(chose==5){
            Del_tree(&tree);
            exit(0);
        }
    }
    return 0;
}
void Init_tree(Tree *ptree){
    ptree->root=NULL;
    ptree->Node_num=0;
}
bool Tree_empty(const Tree *ptree)
bool Tree_full(const Tree *ptree)
int Treenode_num(const Tree *ptree)
bool Add_node(int date,Tree *ptree)
{
    if((Find_node(date,ptree)!=NULL)){
        printf("已存在此项，不可重复添加");
        return false;
    }
    Treenode *operate=(Treenode *)malloc(sizeof(Treenode));
    Treenode *record,*temp;
    int or=0;
    //链接新节点
    if(ptree->root==NULL){
        ptree->root=operate;
    }
    else{
        record=ptree->root;
        while(record){
            temp=record;
            if(date<record->date){
                record=record->left;
                or=LEFT;
            }
            else{
                record=record->right;
                or=RIGHT;
            }
        }
        if(or==LEFT){
            temp->left=operate;
        }
        else{
            temp->right=operate;
        }
    }
    operate->date=date;
    operate->left=NULL;
    operate->right=NULL;
    ptree->Node_num++;
    return 1;
}
int *Find_node(int date,Treenode *operate,Treenode *record,Treenode *parent)
{
    if(operate->date==date){
        record=operate;
        return 0
    }
    parent=operate;
    while(operate){
        Find_node(date,operate->left);
        Find_node(date,operate->right);
    }
}
bool Del_node(int date,Tree *ptree)
{
    Treenode *operate,*record,*parent;
    operate=ptree->root;
    Find_node(date,operate,record,parent);
    
}
void Del_tree(Tree *ptree)
void Display_tree(const Tree *ptree);
