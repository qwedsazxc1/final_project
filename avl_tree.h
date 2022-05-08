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

struct avl_tree{
    struct avlnode *root;
    int (*add)(struct avl_tree *tree, int data);
    int (*max)(struct avl_tree tree);
    int (*min)(struct avl_tree tree);
    int (*height)(struct avl_tree tree);
    void (*clear)(struct avl_tree *tree);
    int (*search)(struct avl_tree tree, int target);
    void (*delete)(struct avl_tree *tree, int target);
};

typedef struct avl_tree avl_tree;

void initial_avl_tree(struct avl_tree *avl_tree);
void print_tree(struct avlnode *node);

#endif