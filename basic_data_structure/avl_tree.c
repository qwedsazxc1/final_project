#include "avl_tree.h"

// build a tree with the information given
static struct avlnode *build_node(void *data, size_t size, struct avlnode *parent);

// insert a node to tree and determine its place
static int insert_node(struct avlnode *node, void *data, size_t size, int (*cmp)(const void *a, const void *b));

// balance the node using right_rotate and left_rotate functions
static void balance(struct avlnode *node);

// left rotate a parent node's children node
static void left_rotate(struct avlnode *node);

// right rotate a parent node's children node
static void right_rotate(struct avlnode *node);

// a function that can find the minimum node in the linked list
static void *min_node(struct avlnode *node);

// a function that can find the maximum node in the linked list
static void *max_node(struct avlnode *node);

// redefine the parent node
static void update_root(struct avlnode **node);

//return the height of node
static int node_height(struct avlnode *node);

//delete the tree
static void free_tree(struct avlnode *node, void (*destroy_data_function)(void *data));

// a function for return the target node for other function
static struct avlnode *search_node(struct avlnode *node, void *target, int(*cmp)(const void *a, const void *b));

// a function that can delete node in the linked list
static struct avlnode *delete_node(struct avlnode *node, void *target, int(*cmp)(const void *a, const void *b), void (*destroy_data_function)(void *data));

// get the successor node in the tree
static struct avlnode *get_successor_node(struct avlnode *node);

// compare two children node and update the height of a tree
static void update_node_height(struct avlnode *node);

// a function for print a tree and use for other function
static void print_tree(struct avlnode *node, int mode, void (*print_func)(const void *data));

// insert new node into the tree
static int insert(avl_tree tree, void *data, size_t size);

// use *max_node function to find the maximum node in the tree
static void *max(const avl_tree tree);

// use *min_node function to find the minimum node in the tree
static void *min(const avl_tree tree);

// return the height of tree
static int height(const avl_tree tree);

// clear the tree to NULL
static void clear(avl_tree tree);

// use the *delete_node function to delete node in the tree
static void delete(avl_tree tree, void *target);

// if node is not NULL use search_node to find the target
static void *search(const avl_tree tree, void *target);

// a function with print tree
static void print_tree(struct avlnode *node, int mode, void (*print_func)(const void *data)){
    if (node == NULL)
        return;

    if (mode == PRE_ORDER)
        print_func(node->data);

    print_tree(node->left_child, mode, print_func);

    if (mode == IN_ORDER)
        print_func(node->data);

    print_tree(node->right_child, mode, print_func);

    if (mode == POST_ORDER)
        print_func(node->data);
}

// print the tree when mode is different with level order
void avl_tree_traversal(avl_tree tree, int mode){
    if (mode != LEVEL_ORDER)
        print_tree(tree->root, mode, tree->print_func);
}

// print the tree with pre order situation
void avl_tree_preorder_traversal(avl_tree tree){
    print_tree(tree->root, PRE_ORDER, tree->print_func);
}

// print the tree with in order situation
void avl_tree_inorder_traversal(avl_tree tree){
    print_tree(tree->root, IN_ORDER, tree->print_func);
}

// print the tree with post order situation
void avl_tree_postorder_traversal(avl_tree tree){
    print_tree(tree->root, POST_ORDER, tree->print_func);
}

// print the tree with level order situation
void avl_tree_level_order_traversal(avl_tree tree){
    queue que;
    initial_queue(&que, tree->destroy_data_function);
    que->push(que, &(tree->root), sizeof(struct avlnode *));
    
    while (!(que->empty(que))){
        struct avlnode *node = *(struct avlnode **)que->front(que);

        if (node == NULL){
            que->pop(que);
            continue;
        }

        tree->print_func(node->data);

        que->push(que, &(node->left_child), sizeof(struct avlnode *));
        que->push(que, &(node->right_child), sizeof(struct avlnode *));
        que->pop(que);
    }
    free(que);
}

//initialization
void initial_avl_tree(avl_tree *avl_tree, int (*cmp)(const void *a, const void *b), void (*print_func)(const void *data)\
, void (*destroy_data_function)(void *data)){
    *avl_tree = malloc(sizeof(struct avl_tree));
    (*avl_tree)->root = NULL;
    (*avl_tree)->insert = insert;
    (*avl_tree)->max = max;
    (*avl_tree)->min = min;
    (*avl_tree)->height = height;
    (*avl_tree)->clear = clear;
    (*avl_tree)->search = search;
    (*avl_tree)->delete = delete;
    (*avl_tree)->cmp = cmp;
    (*avl_tree)->print_func = print_func;
    (*avl_tree)->destroy_data_function = destroy_data_function;
}


static int height(const avl_tree tree){
    return node_height(tree->root);
}


static void left_rotate(struct avlnode *node){
    struct avlnode *parent = (node)->parent, *right = (node)->right_child;
    right->parent = parent;
    if (parent != NULL){
        if (parent->left_child == node)
            parent->left_child = right;
        else
            parent->right_child = right;
    }
    (node)->right_child = right->left_child;
    if ((node)->right_child != NULL)
        (node)->right_child->parent = node;

    (node)->parent = right;
    right->left_child = node;

}

static void right_rotate(struct avlnode *node){
    struct avlnode *parent = (node)->parent, *left = (node)->left_child;
    left->parent = parent;
    if (parent != NULL){
        if (parent->left_child == node)
            parent->left_child = left;
        else
            parent->right_child = left;
    }
    (node)->left_child = left->right_child;
    if ((node)->left_child != NULL)
        (node)->left_child->parent = node;

    left->right_child = node;
    (node)->parent = left;

}

static void balance(struct avlnode *node){
    if (node_height(node->left_child) - node_height(node->right_child) > 1){
        if (node_height(node->left_child->right_child) > node_height(node->left_child->left_child))
            left_rotate(node->left_child);
        
        right_rotate(node);
    }
    if (node_height(node->right_child) - node_height(node->left_child) > 1){
        if (node_height(node->right_child->left_child) > node_height(node->right_child->right_child))
            right_rotate(node->right_child);

        left_rotate(node);
    }

}

static int insert_node(struct avlnode *node, void *data, size_t size, int (*cmp)(const void *a, const void *b)){

    int add_result = 0;
    if (cmp(node->data, data) < 0){
        if ((node)->right_child != NULL)
            add_result = insert_node(((node)->right_child), data, size, cmp);
        else{
            struct avlnode *new_node = build_node(data, size, node);
            if (new_node == NULL){
                set_and_print_error_message("avltree : memory allocation fail\n");
                return -1;
            }
            (node)->right_child = new_node;
            node->depth = 2;
            return 0;
        }
    }
    if (cmp(node->data, data) > 0){
        if ((node)->left_child != NULL)
            add_result = insert_node(((node)->left_child), data, size, cmp);
        else{
            struct avlnode *new_node = build_node(data, size, node);
            if (new_node == NULL){
                set_and_print_error_message("avltree : memory allocation fail\n");
                return -1;
            }
            (node)->left_child = new_node;
            node->depth = 2;
            return 0;
        }
    }
    
    balance(node);
    update_node_height(node);
    return add_result;
}

static int insert(avl_tree tree, void *data, size_t size){
    if (tree->root == NULL){
        struct avlnode *new_node = build_node(data, size, NULL);
        if (new_node == NULL){
            set_and_print_error_message("avltree : memory allocation fail\n");
            return -1;
        }
        tree->root = new_node;
        return 0;
    }
    int add_result = insert_node(tree->root, data, size, tree->cmp);
    update_root(&(tree->root));
    return add_result;
}

static struct avlnode *build_node(void *data, size_t size, struct avlnode *parent){
    struct avlnode *new_node = (struct avlnode *)malloc(sizeof(avlnode));
    if (new_node == NULL)
        return NULL;
    new_node->data = malloc(size);
    memcpy(new_node->data, data, size);
    new_node->left_child = NULL;
    new_node->right_child = NULL;
    new_node->parent = parent;
    new_node->depth = 1;
    return new_node;
}

static void *max(const avl_tree tree){
    return max_node(tree->root);
}

static void *max_node(struct avlnode *node){
    if (node == NULL)
        return NULL;
    
    if (node->right_child == NULL)
        return node->data;

    return max_node(node->right_child);
}

static void *min(const avl_tree tree){
    return min_node(tree->root);
}

static void *min_node(struct avlnode *node){
    if (node == NULL)
        return NULL;
    
    if (node->left_child == NULL)
        return node->data;

    return min_node(node->left_child);
}

static void update_root(struct avlnode **node){
    if (*node == NULL)
        return;
    while ((*node)->parent != NULL)
        *node = (*node)->parent;
}

static int node_height(struct avlnode *node){
    if (node == NULL)
        return 0;
    return node->depth;
}


static void clear(avl_tree tree){
    free_tree(tree->root, tree->destroy_data_function);
    tree->root = NULL;
}

static void free_tree(struct avlnode *node, void (*destroy_data_function)(void *data)){
    if (node == NULL)
        return;

    free_tree(node->left_child, destroy_data_function);
    free_tree(node->right_child, destroy_data_function);
    destroy_data_function(node->data);
    free(node->data);
    free(node);
}

static void delete(avl_tree tree, void *target){
    tree->root = delete_node(tree->root, target, tree->cmp, tree->destroy_data_function);
}

static void *search(const avl_tree tree, void *target){
    struct avlnode *node = search_node(tree->root, target, tree->cmp);
    if (node != NULL)
        return node->data;
    return NULL;
}

static struct avlnode *search_node(struct avlnode *node, void *target, int (*cmp)(const void *a, const void *b)){
    if (node == NULL)
        return NULL;
    
    if (cmp(node->data, target) < 0)
        return search_node(node->right_child, target, cmp);
    
    if (cmp(node->data, target) > 0)
        return search_node(node->left_child, target, cmp);
    
    return node;
}

static struct avlnode *delete_node(struct avlnode *node, void *target, int (*cmp)(const void *a, const void *b), void (*destroy_data_function)(void *data)){
    if (node == NULL){
        set_and_print_error_message("avl_tree (delete) : target not found\n");
        return NULL;
    }
    if (node->data > target){
        node->left_child = delete_node(node->left_child, target, cmp, destroy_data_function);
        balance(node);
        update_node_height(node);
        return node;
    }
    if (node->data < target){
        node->right_child = delete_node(node->right_child, target, cmp, destroy_data_function);
        balance(node);
        update_node_height(node);
        return node;
    }

    if (node->left_child == NULL && node->right_child == NULL){
        free(node->data);
        free(node);
        return NULL;
    }

    if (node->left_child == NULL){
        struct avlnode *right_sub_tree = node->right_child;
        free(node->data);
        free(node);
        right_sub_tree->parent = node;
        return right_sub_tree;
    }

    if (node->right_child == NULL){
        struct avlnode *left_sub_tree = node->left_child;
        free(node->data);
        free(node);
        left_sub_tree->parent = node;
        return left_sub_tree;
    }

    struct avlnode *successor_node = get_successor_node(node->right_child);

    successor_node->parent = node->parent;
    successor_node->left_child = node->left_child;
    successor_node->right_child = node->right_child;
    if (successor_node->parent != NULL){
        if (successor_node->parent->left_child == node)
            successor_node->parent->left_child = successor_node;
        else
            successor_node->parent->right_child = successor_node;
    }
    if (successor_node->left_child != NULL)
        successor_node->left_child->parent = successor_node;
    if (successor_node->right_child != NULL)
        successor_node->right_child->parent = successor_node;
    update_node_height(successor_node);
    struct avlnode *temp_parent_node = successor_node->parent;

    balance(successor_node);
    update_node_height(successor_node);
    free(node->data);
    free(node);
    if (temp_parent_node == successor_node->parent)
        return successor_node;
    else
        return successor_node->parent;
}

static void update_node_height(struct avlnode *node){
    if (node == NULL)
        return;
    int left_child_height = node_height(node->left_child);
    int right_child_height = node_height(node->right_child);
    if (left_child_height > right_child_height)
        node->depth = left_child_height + 1;
    else
        node->depth = right_child_height + 1;
}

static struct avlnode *get_successor_node(struct avlnode *node){
    if (node->left_child == NULL){
        if (node->parent->right_child == node)
            node->parent->right_child = NULL;
        else
            node->parent->left_child = NULL;
        

        return node;
    }


    struct avlnode *successor_node = get_successor_node(node->left_child);
    update_node_height(node);
    balance(node);
    update_node_height(node);
    return successor_node;
}