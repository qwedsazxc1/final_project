#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../error.h"
struct dnode{
    void *data;
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
    struct dnode *(*search_node_from_head)(const list dlist, void *target_data);
    struct dnode *(*search_node_from_tail)(const list dlist, void *target_data);
    int (*push_front)(list dlist, void *data, size_t size);
    int (*push_back)(list dlist, void *data, size_t size);
    void *(*front)(const list dlist);
    void *(*back)(const list dlist);
    int (*size)(const list dlist);
    int (*empty)(const list dlist);
    int (*pop_back)(list dlist);
    int (*pop_front)(list dlist);
    struct dnode *(*begin)(const list dlist);
    struct dnode *(*end)(const list dlist);
    int (*erase)(list dlist, struct dnode *target_node);
    int (*insert)(list dlist, void *data, size_t size, struct dnode *target_node);
    void (*destory)(list dlist);
    void (*destroy_data_function)(void *data);
    int (*cmp)(const void *a, const void *b);
    int (*print_func)(const void *data);
};


// use to initial the list structure
void initial_list(list *list, void (*destroy_data_function)(void *data),
                  int (*cmp)(const void *a, const void *b), int (*print_func)(const void *data));

// use to initial the list structure, but without compare and print function
void simple_initial_list(list *list, void (*destroy_data_function)(void *data));
#endif