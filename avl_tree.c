#include "avl_tree.h"

static struct avlnode *build_node(int data, struct avlnode *parent);
static int add_node(struct avlnode *node, int data);
static void balance(struct avlnode *node);
static void left_rotate(struct avlnode *node);
static void right_rotate(struct avlnode *node);
static int min_node(struct avlnode *node);
static void update_root(struct avlnode **node);
static int node_height(struct avlnode *node);
static void free_tree(struct avlnode *node);
static struct avlnode *search_node(struct avlnode *node, int target);
static struct avlnode *delete_node(struct avlnode *node, int target);
static struct avlnode *get_successor_node(struct avlnode *node);
static void update_node_height(struct avlnode *node);
static void print_tree(struct avlnode *node, int mode);

static int add(avl_tree tree, int data);
static int max(const avl_tree tree);
static int min(const avl_tree tree);
static int height(const avl_tree tree);
static int max_node(struct avlnode *node);
static void clear(avl_tree tree);
static void delete(avl_tree tree, int target);
static int search(const avl_tree tree, int target);

static void print_tree(struct avlnode *node, int mode){
    if (node == NULL)
        return;

    if (mode == PREORDER)
        printf("%d\n", node->data);

    print_tree(node->left_child, mode);

    if (mode == INORDER)
        printf("%d\n", node->data);

    print_tree(node->right_child, mode);

    if (mode == POSTORDER)
        printf("%d\n", node->data);
}

void avl_tree_traversal(avl_tree tree, int mode){
    if (mode != LEVEL_ORDER)
        print_tree(tree->root, mode);
}

void avl_tree_preorder_traversal(avl_tree tree){
    print_tree(tree->root, PREORDER);
}

void avl_tree_inorder_traversal(avl_tree tree){
    print_tree(tree->root, INORDER);
}

void avl_tree_postorder_traversal(avl_tree tree){
    print_tree(tree->root, POSTORDER);
}

void initial_avl_tree(avl_tree *avl_tree){
    *avl_tree = malloc(sizeof(struct avl_tree));
    (*avl_tree)->root = NULL;
    (*avl_tree)->add = add;
    (*avl_tree)->max = max;
    (*avl_tree)->min = min;
    (*avl_tree)->height = height;
    (*avl_tree)->clear = clear;
    (*avl_tree)->search = search;
    (*avl_tree)->delete = delete;
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
    if (node_height((node)->left_child) - node_height((node)->right_child) > 1){
        if (node_height((node)->left_child->right_child) > node_height((node)->left_child->left_child))
            left_rotate(((node)->left_child));
        
        right_rotate(node);
    }
    if (node_height((node)->right_child) - node_height((node)->left_child) > 1){
        if (node_height((node)->right_child->left_child) > node_height((node)->right_child->right_child))
            right_rotate(((node)->right_child));

        left_rotate(node);
    }

}

static int add_node(struct avlnode *node, int data){

    int add_result = 0;
    if ((node)->data < data){
        if ((node)->right_child != NULL)
            add_result = add_node(((node)->right_child), data);
        else{
            struct avlnode *new_node = build_node(data, node);
            if (new_node == NULL){
                set_and_print_error_message("avltree : memory allocation fail\n");
                return -1;
            }
            (node)->right_child = new_node;
            node->depth = 2;
            return 0;
        }
    }
    if ((node)->data > data){
        if ((node)->left_child != NULL)
            add_result = add_node(((node)->left_child), data);
        else{
            struct avlnode *new_node = build_node(data, node);
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

static int add(avl_tree tree, int data){
    if (tree->root == NULL){
        struct avlnode *new_node = build_node(data, NULL);
        if (new_node == NULL){
            set_and_print_error_message("avltree : memory allocation fail\n");
            return -1;
        }
        tree->root = new_node;
        return 0;
    }
    int add_result = add_node(tree->root, data);
    update_root(&(tree->root));
    return add_result;
}

static struct avlnode *build_node(int data, struct avlnode *parent){
    struct avlnode *new_node = (struct avlnode *)malloc(sizeof(avlnode));
    if (new_node == NULL)
        return NULL;
    new_node->data = data;
    new_node->left_child = NULL;
    new_node->right_child = NULL;
    new_node->parent = parent;
    new_node->depth = 1;
    return new_node;
}

static int max(const avl_tree tree){
    return max_node(tree->root);
}

static int max_node(struct avlnode *node){
    if (node == NULL)
        return -1;
    
    if (node->right_child == NULL)
        return node->data;

    return max_node(node->right_child);
}

static int min(const avl_tree tree){
    return min_node(tree->root);
}

static int min_node(struct avlnode *node){
    if (node == NULL)
        return -1;
    
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
    free_tree(tree->root);
    tree->root = NULL;
}

static void free_tree(struct avlnode *node){
    if (node == NULL)
        return;

    free_tree(node->left_child);
    free_tree(node->right_child);
    free(node);
}

static void delete(avl_tree tree, int target){
    tree->root = delete_node(tree->root, target);
}

static int search(const avl_tree tree, int target){
    struct avlnode *node = search_node(tree->root, target);
    if (node != NULL)
        return node->data;
    return -1;
}

static struct avlnode *search_node(struct avlnode *node, int target){
    if (node == NULL){
        set_and_print_error_message("avl_tree (delete) : target not found\n");
        return NULL;
    }
    
    if (target > node->data)
        return search_node(node->right_child, target);
    
    if (target < node->data)
        return search_node(node->right_child, target);
    
    return node;
}

static struct avlnode *delete_node(struct avlnode *node, int target){
    if (node == NULL){
        set_and_print_error_message("avl_tree (delete) : target not found\n");
        return NULL;
    }
    if (node->data > target){
        node->left_child = delete_node(node->left_child, target);
        balance(node);
        update_node_height(node);
        return node;
    }
    if (node->data < target){
        node->right_child = delete_node(node->right_child, target);
        balance(node);
        update_node_height(node);
        return node;
    }

    if (node->left_child == NULL && node->right_child == NULL){
        free(node);
        return NULL;
    }

    if (node->left_child == NULL){
        struct avlnode *right_sub_tree = node->right_child;
        free(node);
        right_sub_tree->parent = node;
        return right_sub_tree;
    }

    if (node->right_child == NULL){
        struct avlnode *left_sub_tree = node->left_child;
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