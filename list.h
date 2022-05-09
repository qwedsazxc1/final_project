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

typedef struct list *list;

struct list{
    size_t list_size;
    struct dnode *head;
    struct dnode *tail;
    void (*print_list_from_head)(const list dlist);
    void (*print_list_from_tail)(const list dlist);
    void (*clear)(list dlist);
    struct dnode *(*search_node_from_head)(const list dlist, int target_data);
    struct dnode *(*search_node_from_tail)(const list dlist, int target_data);
    int (*push_front)(list dlist, int data);
    int (*push_back)(list dlist, int data);
    int (*front)(const list dlist);
    int (*back)(const list dlist);
    int (*size)(const list dlist);
    int (*empty)(const list dlist);
    int (*pop_back)(list dlist);
    int (*pop_front)(list dlist);
    struct dnode *(*begin)(const list dlist);
    struct dnode *(*end)(const list dlist);
    int (*erase)(list dlist, struct dnode *target_node);
    int (*insert)(list dlist, int data, struct dnode *target_node);
};

void initial_double_linked_list(list *list);
#endif