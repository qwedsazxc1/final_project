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
    
    // prints the list from the head (first node) until the last node (tail) , [head -> tail]
    void (*print_list_from_head)(const list dlist);
    
    // prints the list from the tail (last node) until the head node head) , [tail -> head]
    void (*print_list_from_tail)(const list dlist);
    
    // clear the list (delete all nodes in the list)
    void (*clear)(list dlist);
    
    // search the list from head to tail to find the node that stores the specific data.
    void *(*search_node_from_head)(const list dlist, void *target_data);
    
    // search the list from tail to head to find the node that stores the specific data.
    void *(*search_node_from_tail)(const list dlist, void *target_data);
    
    // insert a node as the the head of the list
    int (*push_front)(list dlist, void *data, size_t size);
    
    // insert a node as the the tail of the list
    int (*push_back)(list dlist, void *data, size_t size);
    
    // returns the data stored in the head (head node) of the list
    void *(*front)(const list dlist);
    
    // returns the data stored in the tail (last node) of the list
    void *(*back)(const list dlist);
    
    // return the number of nodes in the list
    int (*size)(const list dlist);
    
    // delete a specific node.
    int (*empty)(const list dlist);
    
    // delete the current tail (last node) of the list
    int (*pop_back)(list dlist);
    
    // delete the current head (first node) of the list
    int (*pop_front)(list dlist);
    
    // get the head (first node) of the list
    struct dnode *(*begin)(const list dlist);
    
    // get the tail (last node) of the list
    struct dnode *(*end)(const list dlist);
    
    // delete a specific node.
    int (*erase)(list dlist, struct dnode *target_node);
    
    // insert a new node in front of the specific node
    int (*insert)(list dlist, void *data, size_t size, struct dnode *target_node);
    
    // delete the current list
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