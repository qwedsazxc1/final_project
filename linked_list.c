#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "linked_list.h" 
#include "lib.h"

struct node *build_node(int data){
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL)
        return NULL;
    new_node->data = data;
    return new_node;
}

struct node *search_target_previous_node(struct node *head, int target){
    struct node *current_node = head, *previous_node = NULL;
    for (; current_node != NULL; previous_node = current_node, current_node = current_node->next)
        if (current_node->data == target)
            break;
    if (current_node == NULL)
        previous_node = NULL;
    return previous_node;
}

struct node *search_target_node(struct node *head, int target){
    struct node *current_node = head;
    for (; current_node != NULL; current_node = current_node->next)
        if (current_node->data == target)
            break;
    
    return current_node;
}

int add_node_to_head(struct node **head, int data){
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL){
        set_and_print_error_message("linked list : allocate memory fail\n");
        return -1;
    }
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
    return 0;
}

int add_node_to_end(struct node **head, int data){
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL){
        set_and_print_error_message("linked list : allocate memory fail\n");
        return -1;
    }

    new_node->data = data;
    new_node->next = NULL;
    struct node *current_node = *head;
    for (; current_node != NULL; current_node = current_node->next)
        if (current_node->next == NULL)
            break;

    if (current_node == NULL)
        *head = new_node;
    else
        current_node->next = new_node;

    return 0;
}

int insert_node_before_target(struct node **head, int target, int data){
    struct node *target_node = search_target_node(*head, target);
    if (target_node == NULL){
        set_and_print_error_message("linked list : target node not found\n");
        return 1;
    }

    
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL){
        set_and_print_error_message("linked list : allocate memory fail\n");
        return -1;
    }

    new_node->data = data;
    new_node->next = target_node;
    struct node *previous_node = search_target_previous_node(*head, target);
    if (previous_node == NULL)
        *head = new_node;
    else
        previous_node->next = new_node;
    return 0;
}

int insert_node_after_target(struct node *head, int target, int data){
    struct node *target_node = search_target_node(head, target);
    if (target_node == NULL){
        set_and_print_error_message("linked list : target node not found\n");
        return 1;
    }

    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL){
        set_and_print_error_message("linked list : allocate memory fail\n");
        return -1;
    }
    new_node->data = data;
    new_node->next = target_node->next;
    target_node->next = new_node;
    return 0;
}

int delete_node(struct node **head, int target){
    struct node *target_node = search_target_node(*head, target);
    if (target_node == NULL){
        set_and_print_error_message("linked list : target node not found\n");
        return 1;
    }
       
    struct node *previous_node = search_target_previous_node(*head, target);
    if (previous_node == NULL)
        *head = target_node->next;
    else
        previous_node->next = target_node->next;
    free(target_node);
    return 0;
}

int swap_node(struct node **head, int target1, int target2){
    if (target1 == target2){
        set_error_message("linked list : swap target is same\n");
        return 2;
    }
    struct node *target1_node = search_target_node(*head, target1);
    struct node *target2_node = search_target_node(*head, target2);
    if (target1_node == NULL || target2_node == NULL){
        set_and_print_error_message("linked list : target node not found\n");
        return 1;
    }
    swap(&(target1_node->next), &(target2_node->next), sizeof(struct node *));
    struct node *target1_previous_node = search_target_previous_node(*head, target1);
    struct node *target2_previous_node = search_target_previous_node(*head, target2);
    if (target1_previous_node != NULL && target2_previous_node != NULL){  
        target1_previous_node->next = target2_node;
        target2_previous_node->next = target1_node;
        return 0;
    }

    if (target1_previous_node == NULL){
        swap(&target1_previous_node, &target2_previous_node, sizeof(struct node *));
        swap(&target1_node, &target2_node, sizeof(struct node *));
    }
    *head = target1_node;
    target1_previous_node->next = target2_node;
    return 0;
}

void print_list(struct node *head){
    fprintf(stdout, "linked list : ");
    for (struct node *currenct = head; currenct != NULL; currenct = currenct->next){
        fprintf(stdout, "%d ", currenct->data);
    }
    fprintf(stdout, "\n");
}