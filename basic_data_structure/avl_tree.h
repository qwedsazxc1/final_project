#ifndef AVL_TREE_H
#define AVL_TREE_H
#include "../error.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PRE_ORDER 0
#define IN_ORDER 1
#define POST_ORDER 2
#define LEVEL_ORDER 3
struct avlnode{
    void *data;
    int depth;
    struct avlnode *parent;
    struct avlnode *left_child;
    struct avlnode *right_child;
};

typedef struct avlnode avlnode;

typedef struct avl_tree *avl_tree;

struct avl_tree{
    struct avlnode *root;
    int (*add)(avl_tree tree, void *data, size_t size);
    void *(*max)(const avl_tree tree);
    void *(*min)(const avl_tree tree);
    int (*height)(const avl_tree tree);
    void (*clear)(const avl_tree tree);
    void *(*search)(const avl_tree tree, void *target);
    void (*delete)(const avl_tree tree, void *target);
    int (*cmp)(const void *a, const void *b);
    void (*print_func)(const void *data);
    void (*destroy_data_function)(void *data);
};

void initial_avl_tree(  avl_tree *avl_tree, int (*cmp)(const void *a, const void *b), void (*print_func)(const void *data), \
                        void (*destroy_data_function)(void *data));
void avl_tree_traversal(avl_tree tree, int mode);
void avl_tree_preorder_traversal(avl_tree tree);
void avl_tree_inorder_traversal(avl_tree tree);
void avl_tree_postorder_traversal(avl_tree tree);
void avl_tree_level_order_traversal(avl_tree tree);

#endif