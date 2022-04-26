#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
struct dnode{
    int data;
    struct dnode *next;
    struct dnode *prev;
};
typedef struct dnode dnode;

struct double_linked_list{
    size_t list_size;
    struct dnode *head;
    struct dnode *tail;
    void (*print_list_from_head)(const struct double_linked_list *dlist);
    void (*print_list_from_tail)(const struct double_linked_list *dlist);
    void (*clear)(struct double_linked_list *dlist);
    struct dnode *(*search_node_from_head)(const struct double_linked_list *dlist, int target_data);
    struct dnode *(*search_node_from_tail)(const struct double_linked_list *dlist, int target_data);
    int (*push_front)(struct double_linked_list *dlist, int data);
    int (*push_back)(struct double_linked_list *dlist, int data);
    int (*front)(const struct double_linked_list *dlist);
    int (*back)(const struct double_linked_list *dlist);
    int (*size)(const struct double_linked_list *dlist);
    int (*empty)(const struct double_linked_list *dlist);
    int (*pop_back)(struct double_linked_list *dlist);
    int (*pop_front)(struct double_linked_list *dlist);
    struct dnode *(*begin)(const struct double_linked_list *dlist);
    struct dnode *(*end)(const struct double_linked_list *dlist);
    int (*erase)(struct double_linked_list *dlist, struct dnode *target_node);
    int (*insert)(struct double_linked_list *dlist, int data, struct dnode *target_node);
};
typedef struct double_linked_list double_linked_list;
void initial_double_linked_list(struct double_linked_list *list);
#endif