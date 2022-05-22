#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "queue.h"
#define PREORDER 0
#define INORDER 1
#define POSTORDER 2
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
    int (*add)(avl_tree tree, void *data, size_t size, int (*cmp)(const void *a, const void *b));
    void *(*max)(const avl_tree tree);
    void *(*min)(const avl_tree tree);
    int (*height)(const avl_tree tree);
    void (*clear)(const avl_tree tree);
    void *(*search)(const avl_tree tree, void *target, int (*cmp)(const void *a, const void *b));
    void (*delete)(const avl_tree tree, void *target, int (*cmp)(const void *a, const void *b));
};

void initial_avl_tree(avl_tree *avl_tree);
void avl_tree_traversal(avl_tree tree, int mode, int (*print_func)(void *data));
void avl_tree_preorder_traversal(avl_tree tree, int (*print_func)(void *data));
void avl_tree_inorder_traversal(avl_tree tree, int (*print_func)(void *data));
void avl_tree_postorder_traversal(avl_tree tree, int (*print_func)(void *data));
void avl_tree_level_order_traversal(avl_tree tree, int (*print_func)(void *data));

#endif