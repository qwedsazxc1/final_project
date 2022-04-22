#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node{
    int data;
    struct node *next;
} node;

struct node *search_target_previous_node(struct node *head, int target);
struct node *search_target_node(struct node *head, int target);
int add_node_to_head(struct node **head, int data);
int add_node_to_end(struct node **head, int data);
int insert_node_before_target(struct node **head, int target, int data);
int insert_node_after_target(struct node *head, int target, int data);
int delete_node(struct node **head, int target);
int swap_node(struct node **head, int target1, int target2);
void print_list(struct node *head);

#endif