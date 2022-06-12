#include "list.h"

// build a node with the information given
static struct dnode *build_node(void *data, size_t size, struct dnode *next, struct dnode *prev);     

// add node at the head, making the newnode be the new head of the list. 
static int add_node_to_head(struct dnode **head, struct dnode **tail, void *data, size_t size);         

// add node at the tail, making the newnode be the new tail of the list.
static int add_node_to_tail(struct dnode **head, struct dnode **tail, void *data, size_t size);                                  

// delete a specific node from list
static int delete_node(struct dnode **head, struct dnode **tail, struct dnode *target_node, void (*destroy_data_function)(void *data)); 

// insert a next node next of the target node (new_node is the next node of target_node)
static int insert_node(struct dnode **head, void *data, size_t size, struct dnode *target_node);                                       

// prints the list from the head (first node) until the last node (tail) , [head -> tail]
static void print_list_from_head(const list dlist);                                 

// prints the list from the tail (last node) until the head node head) , [tail -> head]
static void print_list_from_tail(const list dlist);                                 

// clear the list (delete all nodes in the list)
static void clear(list dlist); 

// insert a node as the the head of the list
static int push_front(list dlist, void *data, size_t size);            

// insert a node as the the tail of the list
static int push_back(list dlist, void *data, size_t size);  

// returns the data stored in the head (head node) of the list
static void *front(const list dlist);     

// returns the data stored in the tail (last node) of the list
static void *back(const list dlist);         

// return the number of nodes in the list   
static int size(const list dlist);     

// check if the list is empty
static int empty(const list dlist);       

// delete the current tail (last node) of the list
static int pop_back(list dlist);      

// delete the current head (first node) of the list
static int pop_front(list dlist);         

// get the head (first node) of the list
static struct dnode *begin(const list dlist);         

// get the tail (last node) of the list
static struct dnode *end(const list dlist);    

// search the list from head to tail to find the node that stores the specific data.
static void *search_node_from_head(const list dlist, void *target_data);    

// search the list from tail to head to find the node that stores the specific data.
static void *search_node_from_tail(const list dlist, void *target_data);  

// delete a specific node.
static int erase(list dlist, struct dnode *target_node);                      

// insert a new node in front of the specific node
static int insert(list dlist, void *data, size_t size, struct dnode *target_node); 

// delete the current list
static void destory(list dlist);                                                    

void initial_list(  list *list, void (*destroy_data_function)(void *data), \
                    int (*cmp)(const void *a, const void *b), int (*print_func)(const void *data)){    //makes all function pointers point to functions
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

void simple_initial_list(list *list, void (*destroy_data_function)(void *data)){        //makes all function pointers point to functions
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
    struct dnode *new_node = (struct dnode *)malloc(sizeof(struct dnode));  //provide memory with size of struct dnode
    if (new_node == NULL)  //determine if the malloc() is succefully executed.
        return NULL;
    new_node->data = malloc(size);  //provide space for data.  
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
    if (*head == NULL && *tail == NULL){  //if the list is just created, which means currently only one node inside the list
        *head = new_node;
        *tail = new_node;
        return 0;
    }
    (*head)->prev = new_node;  //the old head (first node) of the list becomes the second node of the list and its prev node is the newly created node.
    *head = new_node;  //make the newly created node as the head of the list
    return 0;
}

static int add_node_to_tail(struct dnode **head, struct dnode **tail, void *data, size_t size){
    struct dnode *new_node = build_node(data, size, NULL, *tail);
    if (new_node == NULL){
        set_and_print_error_message("double linked list : allocate memory fail\n");
        return -1;
    }
    if (*head == NULL && *tail == NULL){  //if the list is just created, which means currently only one node inside the list
        *head = new_node;
        *tail = new_node;
        return 0;
    }

    (*tail)->next = new_node; //the old tail (last node) of the list becomes the last second node of the list and its next node is the newly created node.
    *tail = new_node;         //make the newly created node as the tail of the list
    return 0;
}

static void print_list_from_head(const list dlist){  
    for (struct dnode *cur = dlist->head; cur != NULL; cur = cur->next)  //for each loop, move to the next node by dereference the pointer dnode* next of the current node.
        dlist->print_func(cur->data);

}

static void clear(list dlist){ 
    for (struct dnode *cur = dlist->head; cur != NULL;){ //travel the list from head to tail and delete the nodes until it reaches NULL
        struct dnode *temp = cur;  //tmp store the address of current node
        cur = cur->next;  //make the new current node be the next node of the current node
        free(temp->data); //remove the node pointed by tmp
        free(temp);
    }
    dlist->head = NULL;
    dlist->tail = NULL;
}
static void print_list_from_tail(const list dlist){       
    for (struct dnode *cur = dlist->tail; cur != NULL; cur = cur->prev) //for each loop, move to the prev node by dereference the pointer dnode* prev of the current node.
        dlist->print_func(cur->data);

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
    if (cur == NULL){  //if the specific node requested to be deleted does not exist in list
        set_and_print_error_message("double linked list : delete target not found\n");
        return 1;
    }
    struct dnode *prev_node = cur->prev;
    struct dnode *next_node = cur->next;
    if (prev_node == NULL && next_node == NULL){  //if the list only contains one node.
        destroy_data_function(cur->data);
        free(cur->data);    
        free(cur);
        *head = NULL;
        *tail = NULL;
        return 0;
    }
    if (prev_node == NULL){  //if cur is the head (first node) of the list
        next_node->prev = NULL;  
        *head = next_node;
        destroy_data_function(cur->data);
        free(cur->data);
        free(cur);
        return 0;
    }
    if (next_node == NULL){ //if cur is the tail (last node) of the list
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
static void *search_node_from_head(const list dlist, void *target_data){  
    struct dnode *cur;
    for (cur = dlist->head; cur != NULL; cur = cur->next){
        if (dlist->cmp(target_data, cur->data) == 0)
            break;
    }

    if (cur == NULL)
        return NULL;
    return cur->data;
}
static void *search_node_from_tail(const list dlist, void *target_data){  
    struct dnode *cur;
    for (cur = dlist->tail; cur != NULL; cur = cur->prev){
        if (dlist->cmp(target_data, cur->data) == 0)
            break;
    }

    if (cur == NULL)
        return NULL;
    return cur->data;
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
    if (target_node == *head) //if the target node is actually the head of the node, the it does the operation just like add_node_to_head
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