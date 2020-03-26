/*************************************************************************
	> File Name: bintree.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月24日 星期二 21时39分17秒
 ************************************************************************/
//动态创建二叉查找树
#include<stdio.h>
#include"bintree.h"
#define LEFT 1
#define RIGHT 2
int main()
{
    Tree tree;
    Init_tree(&tree);
    while(1){
        printf("\n1.添加节点\n2.删除节点\n3.查找节点\n4.遍历二叉树\n5.清空退出\n");
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
            Treenode *record,*parent;//准备参数
            parent=tree.root;
            record=NULL;
            Find_node(date,tree.root,&record,&parent);
            if(record!=NULL){
                printf("存在%d",record->date);
            }
            else{
                printf("不存在");
            }
        }else if(chose==4){
            if(tree.root==NULL){
                printf("当前树为空树");
            }
            Display_tree(tree.root);
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
/*bool Tree_empty(const Tree *ptree)
bool Tree_full(const Tree *ptree)
int Treenode_num(const Tree *ptree)*/
int Add_node(int date,Tree *ptree)
{
    //检查是否重复
    Treenode *record,*parent;
    parent=ptree->root;
    record=NULL;
    Find_node(date,ptree->root,&record,&parent);
    if(record!=NULL){
        printf("已存在此项，不可重复添加");
        return 0;
    }
    //为新数据分配空间储存
    Treenode *operate=(Treenode *)malloc(sizeof(Treenode));
    Treenode *temp;
    int or=0;
    //链接新节点
    //第一个节点
    if(ptree->root==NULL){
        ptree->root=operate;
    }
    //第二个节点开始
    else{
        //根据数据大小寻找在树中位置
        record=ptree->root;
        while(record){
            temp=record;//每次记录指针当前所在节点，该记录最终为恰当位置的父节点
            //往左走
            if(date<record->date){
                record=record->left;
                or=LEFT;
            }
            //往右走
            else{
                record=record->right;
                or=RIGHT;
            }
        }
        //把新节点地址储存
        if(or==LEFT){
            temp->left=operate;
        }
        else{
            temp->right=operate;
        }
    }
    //拷贝数据
    operate->date=date;
    operate->left=NULL;
    operate->right=NULL;
    /*printf("%p",operate);调试*/
    ptree->Node_num++;//节点数增加
    return 1;
}
int Find_node(int date,Treenode *operate,Treenode **record,Treenode **parent)
{
    if(operate){
        //若找到相同数据则记录下节点地址并结束
        if(operate->date==date){
            (*record)=operate;
            return 1;
        }
        //递归遍历
        Find_node(date,operate->left,record,parent);
        Find_node(date,operate->right,record,parent);
        //每次记录当前节点，一旦parent为record的父节点则不再改变parent
        if((*parent)->left==(*record) || (*parent)->right==(*record)){
            return 1;
        }
        else{
            (*parent)=operate;
        }
    }
}
int Del_node(int date,Tree *ptree)
{
    Treenode *operate,*record,*parent,*temp;
    parent=ptree->root;
    operate=ptree->root;
    record=NULL;
    //调用Find_node函数寻找节点，并记录下节点与其父节点地址
    Find_node(date,operate,&record,&parent);
    if(record==NULL){
        printf("找不到此数据\n");
        return 0;
    }
    else{
        if(record==ptree->root){//节点为树根
            ptree->root=record->left;//以树根的左节点为根，寻找左子树的右指针第一个空节点来链接树根的右子树
            operate=record->left;
            while(operate){
                temp=operate;
                operate=operate->right;
            }
            temp->right=record->right;
        }else if(record->left==NULL && record->right==NULL){//节点左右指针都为空，直接将父节点的某个指针设置为NULL
            if(parent->left==record){
                free(record);
                parent->left=NULL;
            }
            else{
                free(record);
                parent->right=NULL;
            }
        }else if(record->left!=NULL && record->right!=NULL){//节点左右指针都不为空
            if(parent->left==record){
                parent->left=record->left;
                //链接左节点
                operate=record->left;
                //节点往右寻找空节点并链接右节点
                while(operate){
                    temp=operate;
                    operate=operate->right;
                }
                temp->right=record->right;
                free(record);
            }
            else{
                parent->right=record->left;
                operate=record->left;
                while(operate){
                    temp=operate;
                    operate=operate->right;
                }
                temp->right=record->right;
                free(record); 
            }
        }else{//节点左右只有一个为空，直接将其子树与其父子树链接
            if(parent->left==record){
                if(record->left==NULL){
                    parent->left=record->right;
                }
                else{
                    parent->left=record->left;
                }
            }
            else{
                if(record->left==NULL){
                    parent->right=record->right;
                }
                else{
                    parent->right=record->left;
                }
            }
            free(record);
        }
    }
    ptree->Node_num--;//节点数减少
    return 0;
}
void Del_allnode(Treenode *operate)
{
    Treenode *record;
    if(operate!=NULL){
        record=operate->right;//记录下节点的右子树
        Del_allnode(operate->left);//递归删除左子树
        free(operate);
        Del_allnode(record);//递归删除右子树
    }
}
void Del_tree(Tree *ptree)
{
    if(ptree!=NULL){
        Del_allnode(ptree->root);
    }
    //将树设置为空
    ptree->root=NULL;
    ptree->Node_num=0;
}
void Display_tree(const Treenode *operate)
{
    //中序递归遍历
    if(operate){
        Display_tree(operate->left);
        printf("%d ",operate->date);
        Display_tree(operate->right);
    }
}
