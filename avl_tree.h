#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
struct avlnode{
    int data;
    int depth;
    struct avlnode *parent;
    struct avlnode *left_child;
    struct avlnode *right_child;
};

typedef struct avlnode avlnode;

typedef struct avl_tree *avl_tree;

struct avl_tree{
    struct avlnode *root;
    int (*add)(avl_tree tree, int data);
    int (*max)(const avl_tree tree);
    int (*min)(const avl_tree tree);
    int (*height)(const avl_tree tree);
    void (*clear)(const avl_tree tree);
    int (*search)(const avl_tree tree, int target);
    void (*delete)(const avl_tree tree, int target);
};

void initial_avl_tree(avl_tree avl_tree);
void print_tree(struct avlnode *node);

#endif