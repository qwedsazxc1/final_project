#include "double_linked_list.h"

static struct dnode *build_node(int data, struct dnode *next, struct dnode *prev);
static struct dnode *search_node(struct dnode *node, int target);
static int add_node_to_head(struct dnode **head, struct dnode **tail, int data);
static int add_node_to_tail(struct dnode **head, struct dnode **tail, int data);
static void print_list_from_head(struct dnode *head);
static void print_list_from_tail(struct dnode *head);
static int delete_node(struct dnode **head, struct dnode **tail, int target, struct dnode *start_node);
static void clear(struct double_linked_list *dlist);
static int push_front(struct double_linked_list *dlist, int data);
static int push_back(struct double_linked_list *dlist, int data);
static int front(struct double_linked_list *dlist);
static int back(struct double_linked_list *dlist);
static int size(struct double_linked_list *dlist);
static int empty(struct double_linked_list *dlist);
static int pop_back(struct double_linked_list *dlist);
static int pop_front(struct double_linked_list *dlist);

void initial_double_linked_list(struct double_linked_list *list){
    list->list_size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->print_list_from_head = print_list_from_head;
    list->print_list_from_tail = print_list_from_tail;
    list->clear = clear;
    list->push_front = push_front;
    list->push_back = push_back;
    list->front = front;
    list->back = back;
    list->size = size;
    list->empty = empty;
    list->pop_back = pop_back;
    list->pop_front = pop_front;
}

static struct dnode *build_node(int data, struct dnode *next, struct dnode *prev){
    struct dnode *new_node = (struct dnode *)malloc(sizeof(struct dnode));
    if (new_node == NULL)
        return NULL;
    new_node->data = data;
    new_node->next = next;
    new_node->prev = prev;
    return new_node;
}
static int add_node_to_head(struct dnode **head, struct dnode **tail, int data){
    struct dnode *new_node = build_node(data, *head, NULL);
    if (new_node == NULL){
        set_and_print_error_message("double linked list : allocate memory fail\n");
        return -1;
    }
    if (*tail == NULL)
        *tail = new_node;
    *head = new_node;
    return 0;
}

static int add_node_to_tail(struct dnode **head, struct dnode **tail, int data){
    struct dnode *new_node = build_node(data, NULL, *tail);
    if (new_node == NULL){
        set_and_print_error_message("double linked list : allocate memory fail\n");
        return -1;
    }
    if (*head == NULL)
        *head = new_node;
    *tail = new_node;
    return 0;
}

static void print_list_from_head(struct dnode *head){
    printf("list (from head) : ");
    for (struct dnode *cur = head; cur != NULL; cur = cur->next)
        printf("%d ", cur->data);
    
    printf("\n");
}

static void clear(struct double_linked_list *dlist){
    for (struct dnode *cur = dlist->head; cur != NULL;){
        struct dnode *temp = cur;
        cur = cur->next;
        free(temp);
    }
    dlist->head = NULL;
    dlist->tail = NULL;
}
static void print_list_from_tail(struct dnode *tail){
    printf("list (from tail) : ");
    for (struct dnode *cur = tail; cur != NULL; cur = cur->prev)
        printf("%d ", cur->data);
    
    printf("\n");
}

static int push_front(struct double_linked_list *dlist, int data){
    int push_result = add_node_to_head(&(dlist->head), &(dlist->tail), data);
    if (!push_result)
        dlist->list_size += 1;
    return push_result;
}

static int push_back(struct double_linked_list *dlist, int data){
    int push_result = add_node_to_tail(&(dlist->head), &(dlist->tail), data);
    if (!push_result)
        dlist->list_size += 1;
    return push_result;
}

static int front(struct double_linked_list *dlist){
    if (dlist->empty(dlist))
        return -1;

    return dlist->head->data;
}

static int back(struct double_linked_list *dlist){
    if (dlist->empty(dlist))
        return -1;

    return dlist->head->data;
}

static int size(struct double_linked_list *dlist){
    return dlist->list_size;
}

static int empty(struct double_linked_list *dlist){
    if (dlist->size == 0)
        return 1;

    return 0;
}

static int delete_node(struct dnode **head, struct dnode **tail, int target, struct dnode *start_node){
    struct dnode *cur;
    cur = search_node(start_node, target);
    if (cur == NULL){
        set_and_print_error_message("double linked list : delete target not found\n");
        return 1;
    }
    struct dnode *prev_node = cur->prev;
    struct dnode *next_node = cur->next;
    if (prev_node == NULL && next_node == NULL){
        free(cur);
        *head = NULL;
        *tail = NULL;
        return 0;
    }
    if (prev_node == NULL){
        next_node->prev = NULL;
        *head = next_node;
        free(cur);
        return 0;
    }
    if (next_node == NULL){
        prev_node->next = NULL;
        *tail = prev_node;
        free(cur);
        return 0;
    }
    next_node->prev = prev_node;
    prev_node->next = next_node;
    free(cur);
    return 0;
}

static int pop_back(struct double_linked_list *dlist){
    int pop_result = delete_node(&(dlist->head), &(dlist->tail), dlist->back(dlist), dlist->tail);
    if (!pop_result)
        dlist->size -= 1;

    return pop_result;
}

static struct dnode *search_node(struct dnode *node, int target){
    struct dnode *cur;
    if (node == NULL)
        return NULL;
    if (node->next == NULL && node->prev != NULL){
        for (cur = node; cur != NULL; cur = cur->prev){
            if (cur->data == target)
                break;
        }
        return cur;
    }

    for (cur = node; cur != NULL; cur = cur->next){
        if (cur->data == target)
            break;
    }
    return cur;
}

static int pop_front(struct double_linked_list *dlist){
    int pop_result = delete_node(&(dlist->head), &(dlist->tail), dlist->front(dlist), dlist->head);
    if (!pop_result)
        dlist->size -= 1;

    return pop_result;
}

