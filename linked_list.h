#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "lib.h"

#ifndef LINKED_LIST_STRUCT
#define LINKED_LIST_STRUCT
struct node{
    int data;
    struct node *next;
};
#endif
#ifndef LINKED_LIST
#define LINKED_LIST
struct list{
    struct node *head;

    struct node *(*search_target_previous_node)(struct node *head, int target);
    struct node *(*search_target_node)(struct node *head, int target);
    int (*add_node_to_head)(struct node **head, int data);
    int (*add_node_to_end)(struct node **head, int data);
    int (*insert_node_before_target)(struct node **head, int target, int data);
    int (*insert_node_after_target)(struct node *head, int target, int data);
    int (*delete_node)(struct node **head, int target);
    int (*swap_node)(struct node **head, int target1, int target2);
    void (*print_list)(struct node *head);
    void (*clean)(struct node **head);
};
#endif
typedef struct node node;
typedef struct list list;

void initial_list(struct list *data);

#endif