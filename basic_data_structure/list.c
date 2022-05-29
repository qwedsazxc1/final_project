#include "list.h"

static struct dnode *build_node(void *data, size_t size, struct dnode *next, struct dnode *prev);
static int add_node_to_head(struct dnode **head, struct dnode **tail, void *data, size_t size);
static int add_node_to_tail(struct dnode **head, struct dnode **tail, void *data, size_t size);
static int delete_node(struct dnode **head, struct dnode **tail, struct dnode *target_node, void (*destroy_data_function)(void *data));
static int insert_node(struct dnode **head, void *data, size_t size, struct dnode *target_node);

static void print_list_from_head(const list dlist);
static void print_list_from_tail(const list dlist);
static void clear(list dlist);
static int push_front(list dlist, void *data, size_t size);
static int push_back(list dlist, void *data, size_t size);
static void *front(const list dlist);
static void *back(const list dlist);
static int size(const list dlist);
static int empty(const list dlist);
static int pop_back(list dlist);
static int pop_front(list dlist);
static struct dnode *begin(const list dlist);
static struct dnode *end(const list dlist);
static struct dnode *search_node_from_head(const list dlist, void *target_data);
static struct dnode *search_node_from_tail(const list dlist, void *target_data);
static int erase(list dlist, struct dnode *target_node);
static int insert(list dlist, void *data, size_t size, struct dnode *target_node);
static void destory(list dlist);

void initial_list(  list *list, void (*destroy_data_function)(void *data), \
                    int (*cmp)(const void *a, const void *b), int (*print_func)(const void *data)){
    *list = malloc(sizeof(struct list));
    (*list)->list_size = 0;
    (*list)->head = NULL;
    (*list)->tail = NULL;
    (*list)->print_list_from_head = print_list_from_head;
    (*list)->print_list_from_tail = print_list_from_tail;
    (*list)->clear = clear;
    (*list)->push_front = push_front;
    (*list)->push_back = push_back;
    (*list)->front = front;
    (*list)->back = back;
    (*list)->size = size;
    (*list)->empty = empty;
    (*list)->pop_back = pop_back;
    (*list)->pop_front = pop_front;
    (*list)->begin = begin;
    (*list)->end = end;
    (*list)->insert = insert;
    (*list)->erase = erase;
    (*list)->search_node_from_head = search_node_from_head;
    (*list)->search_node_from_tail = search_node_from_tail;
    (*list)->destory = destory;
    (*list)->destroy_data_function = destroy_data_function;
    (*list)->cmp = cmp;
    (*list)->print_func = print_func;
}

void simple_initial_list(list *list, void (*destroy_data_function)(void *data)){
    *list = malloc(sizeof(struct list));
    (*list)->list_size = 0;
    (*list)->head = NULL;
    (*list)->tail = NULL;
    (*list)->print_list_from_head = print_list_from_head;
    (*list)->print_list_from_tail = print_list_from_tail;
    (*list)->clear = clear;
    (*list)->push_front = push_front;
    (*list)->push_back = push_back;
    (*list)->front = front;
    (*list)->back = back;
    (*list)->size = size;
    (*list)->empty = empty;
    (*list)->pop_back = pop_back;
    (*list)->pop_front = pop_front;
    (*list)->begin = begin;
    (*list)->end = end;
    (*list)->insert = insert;
    (*list)->erase = erase;
    (*list)->search_node_from_head = search_node_from_head;
    (*list)->search_node_from_tail = search_node_from_tail;
    (*list)->destory = destory;
    (*list)->destroy_data_function = destroy_data_function;
}

static struct dnode *build_node(void *data, size_t size, struct dnode *next, struct dnode *prev){
    struct dnode *new_node = (struct dnode *)malloc(sizeof(struct dnode));
    if (new_node == NULL)
        return NULL;
    new_node->data = malloc(size);
    memcpy(new_node->data, data, size);
    new_node->next = next;
    new_node->prev = prev;
    return new_node;
}
static int add_node_to_head(struct dnode **head, struct dnode **tail, void *data, size_t size){
    struct dnode *new_node = build_node(data, size, *head, NULL);
    if (new_node == NULL){
        set_and_print_error_message("double linked list : allocate memory fail\n");
        return -1;
    }
    if (*head == NULL && *tail == NULL){
        *head = new_node;
        *tail = new_node;
        return 0;
    }
    (*head)->prev = new_node;
    *head = new_node;
    return 0;
}

static int add_node_to_tail(struct dnode **head, struct dnode **tail, void *data, size_t size){
    struct dnode *new_node = build_node(data, size, NULL, *tail);
    if (new_node == NULL){
        set_and_print_error_message("double linked list : allocate memory fail\n");
        return -1;
    }
    if (*head == NULL && *tail == NULL){
        *head = new_node;
        *tail = new_node;
        return 0;
    }

    (*tail)->next = new_node;
    *tail = new_node;
    return 0;
}

static void print_list_from_head(const list dlist){
    printf("list (from head) : ");
    for (struct dnode *cur = dlist->head; cur != NULL; cur = cur->next)
        dlist->print_func(cur->data);

    printf("\n");
}

static void clear(list dlist){
    for (struct dnode *cur = dlist->head; cur != NULL;){
        struct dnode *temp = cur;
        cur = cur->next;
        free(temp->data);
        free(temp);
    }
    dlist->head = NULL;
    dlist->tail = NULL;
}
static void print_list_from_tail(const list dlist){
    printf("list (from tail) : ");
    for (struct dnode *cur = dlist->tail; cur != NULL; cur = cur->prev)
        dlist->print_func(cur->data);

    printf("\n");
}

static int push_front(list dlist, void *data, size_t size){
    int push_result = add_node_to_head(&(dlist->head), &(dlist->tail), data, size);
    if (!push_result)
        dlist->list_size += 1;
    return push_result;
}

static int push_back(list dlist, void *data, size_t size){
    int push_result = add_node_to_tail(&(dlist->head), &(dlist->tail), data, size);
    if (!push_result)
        dlist->list_size += 1;
    return push_result;
}

static void *front(const list dlist){
    if (dlist->empty(dlist))
        return NULL;

    return dlist->head->data;
}

static void *back(const list dlist){
    if (dlist->empty(dlist))
        return NULL;

    return dlist->tail->data;
}

static int size(const list dlist){
    return dlist->list_size;
}

static int empty(const list dlist){
    if (dlist->list_size == 0)
        return 1;

    return 0;
}

static int delete_node(struct dnode **head, struct dnode **tail, struct dnode *target_node, void (*destroy_data_function)(void *data)){
    struct dnode *cur = target_node;
    if (cur == NULL){
        set_and_print_error_message("double linked list : delete target not found\n");
        return 1;
    }
    struct dnode *prev_node = cur->prev;
    struct dnode *next_node = cur->next;
    if (prev_node == NULL && next_node == NULL){
        destroy_data_function(cur->data);
        free(cur->data);    
        free(cur);
        *head = NULL;
        *tail = NULL;
        return 0;
    }
    if (prev_node == NULL){
        next_node->prev = NULL;
        *head = next_node;
        destroy_data_function(cur->data);
        free(cur->data);
        free(cur);
        return 0;
    }
    if (next_node == NULL){
        prev_node->next = NULL;
        *tail = prev_node;
        destroy_data_function(cur->data);
        free(cur->data);
        free(cur);
        return 0;
    }
    next_node->prev = prev_node;
    prev_node->next = next_node;
    destroy_data_function(cur->data);
    free(cur->data);
    free(cur);
    return 0;
}

static int pop_back(list dlist){
    int pop_result = delete_node(&(dlist->head), &(dlist->tail), dlist->tail, dlist->destroy_data_function);
    if (!pop_result)
        dlist->list_size -= 1;

    return pop_result;
}

static int pop_front(list dlist){
    int pop_result = delete_node(&(dlist->head), &(dlist->tail), dlist->head, dlist->destroy_data_function);
    if (!pop_result)
        dlist->list_size -= 1;

    return pop_result;
}

static struct dnode *begin(const list dlist){
    return dlist->head;
}

static struct dnode *end(const list dlist){
    return dlist->tail;
}
static struct dnode *search_node_from_head(const list dlist, void *target_data){
    struct dnode *cur;
    for (cur = dlist->head; cur != NULL; cur = cur->next){
        if (dlist->cmp(target_data, cur->data) == 0)
            break;
    }
    return cur;
}
static struct dnode *search_node_from_tail(const list dlist, void *target_data){
    struct dnode *cur;
    for (cur = dlist->tail; cur != NULL; cur = cur->prev){
        if (dlist->cmp(target_data, cur->data) == 0)
            break;
    }
    return cur;
}

static int erase(list dlist, struct dnode *target_node){
    int delete_result = delete_node(&(dlist->head), &(dlist->tail), target_node, dlist->destroy_data_function);
    if (!delete_result)
        dlist->list_size -= 1;
    return delete_result;
}

static int insert_node(struct dnode **head, void *data, size_t size, struct dnode *target_node){
    if (target_node == NULL){
        set_and_print_error_message("double linked list : insert target node not found\n");
        return 1;
    }
    struct dnode *new_node = build_node(data, size, target_node, target_node->prev);
    if (new_node == NULL){
        set_and_print_error_message("double linked list : insert node memory allocate fail\n");
        return -1;
    }
    if (target_node == *head)
        *head = new_node;
    target_node->prev = new_node;
    return 0;
}

static int insert(list dlist, void *data, size_t size, struct dnode *target_node){
    int insert_result = insert_node(&(dlist->head), data, size, target_node);
    if (!insert_result)
        dlist->list_size += 1;
    return insert_result;
}

static void destory(list dlist){
    dlist->clear(dlist);
    free(dlist);
}