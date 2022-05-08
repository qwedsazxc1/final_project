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

struct list{
    size_t list_size;
    struct dnode *head;
    struct dnode *tail;
    void (*print_list_from_head)(const struct list *dlist);
    void (*print_list_from_tail)(const struct list *dlist);
    void (*clear)(struct list *dlist);
    struct dnode *(*search_node_from_head)(const struct list *dlist, int target_data);
    struct dnode *(*search_node_from_tail)(const struct list *dlist, int target_data);
    int (*push_front)(struct list *dlist, int data);
    int (*push_back)(struct list *dlist, int data);
    int (*front)(const struct list *dlist);
    int (*back)(const struct list *dlist);
    int (*size)(const struct list *dlist);
    int (*empty)(const struct list *dlist);
    int (*pop_back)(struct list *dlist);
    int (*pop_front)(struct list *dlist);
    struct dnode *(*begin)(const struct list *dlist);
    struct dnode *(*end)(const struct list *dlist);
    int (*erase)(struct list *dlist, struct dnode *target_node);
    int (*insert)(struct list *dlist, int data, struct dnode *target_node);
};
typedef struct list list;
void initial_double_linked_list(struct list *list);
#endif