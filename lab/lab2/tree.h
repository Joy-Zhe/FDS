#ifndef _TREE_H_
#define _TREE_H_
#include<stdio.h>
#include<stdlib.h>
struct tree{
    int pos_A;
    int pos_B;
    struct tree *child;
    struct tree *brother;
    struct tree *father;
};
typedef struct tree * TreeNode;

void AddTreeNode(TreeNode father, TreeNode tmp){
    if(father->child){
        father = 
    }
}
void AddNode(TreeNode father, TreeNode n){
    if(father->child){
        father = father->child;
        while(father->brother)
            father = father->brother;
        father->brother = new;
    }else
        father->child = new;
}
void Delete_branch(TreeNode father);
void voting(TreeNode root, int depth, int n_A, int n_B){
    TreeNode tmp;
    for(int i = n_A - depth + 1; i <= n_A; i++){
        for(int j = n_B - depth + 1; j <= n_B; j++){
            tmp->brother = NULL;
            tmp->child = NULL;
            tmp->pos_A = i;
            tmp->pos_B = j;
            AddNode(root, tmp);
        }
    }
}
void create_voting(TreeNode root, int depth, int n_A, int n_B){
    for(int i = 1; i <= n_A; i++){
        for(int j = 1; j <= n_B; j++){
            
        }
    }
}
#endif