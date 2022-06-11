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

    // insert a new element into tree
    int (*insert)(avl_tree tree, void *data, size_t size);

    // find the max element in tree
    void *(*max)(const avl_tree tree);

    // find the min element in tree
    void *(*min)(const avl_tree tree);

    // get the height from two child node
    // and update the height of node
    int (*height)(const avl_tree tree);

    // destory all the tree
    void (*clear)(const avl_tree tree);

    // search the node that is equal to data
    // return the pointer of data
    void *(*search)(const avl_tree tree, void *target);

    // delete the target node that equal to data
    void (*delete)(const avl_tree tree, void *target);

    // decision the order of tree
    int (*cmp)(const void *a, const void *b);

    // a function can visited data
    // for tree traversal
    void (*print_func)(const void *data);

    // to free the space that occur by datatype store in tree
    void (*destroy_data_function)(void *data);
};

// initial the avl tree be declare or destory
void initial_avl_tree(  avl_tree *avl_tree, int (*cmp)(const void *a, const void *b), void (*print_func)(const void *data), \
                        void (*destroy_data_function)(void *data));

// avl tree traversal function with four mode
// IN_ORDER, PRE_ORDER, POST_ORDER, LEVEL_ORDER
void avl_tree_traversal(avl_tree tree, int mode);

// avl tree pre-order traversal function
void avl_tree_preorder_traversal(avl_tree tree);

// avl tree in-order traversal function
void avl_tree_inorder_traversal(avl_tree tree);

// avl tree post-order traversal function
void avl_tree_postorder_traversal(avl_tree tree);

// avl tree level order traversal function
void avl_tree_level_order_traversal(avl_tree tree);

#endif