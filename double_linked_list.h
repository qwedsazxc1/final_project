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
    void (*print_list_from_head)(struct dnode *head);
    void (*print_list_from_tail)(struct dnode *head);
    void (*clear)(struct double_linked_list *dlist);
    int (*push_front)(struct double_linked_list *dlist, int data);
    int (*push_back)(struct double_linked_list *dlist, int data);
    int (*front)(struct double_linked_list *dlist);
    int (*back)(struct double_linked_list *dlist);
    int (*size)(struct double_linked_list *dlist);
    int (*empty)(struct double_linked_list *dlist);
    int (*pop_back)(struct double_linked_list *dlist);
    int (*pop_front)(struct double_linked_list *dlist);
};
typedef struct double_linked_list double_linked_list;
void initial_double_linked_list(struct double_linked_list *list);
#endif