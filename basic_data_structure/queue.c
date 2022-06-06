#include "queue.h"
//return the list at front of the queue
static void *front(const queue queue);
//return the list at back of the queue
static void *back(const queue queue);
//insert an element from the back of queue 
static int push(queue queue, void *data, size_t size);
//delete an element from head of queue
static int pop(queue queue);
//return the size of queue
static size_t size(const queue queue);
// check if the queue is empty
static int empty(const queue queue);
// pop all elements until nothing left
static void clear(queue queue);
// delete the current queue
static void destory(queue queue);

void initial_queue(queue *queue, void (*destory_data_function)(void *data)){
    *queue = malloc(sizeof(struct queue));
    (*queue)->queue_size = 0;
    simple_initial_list(&(*queue)->list, destory_data_function);
    (*queue)->front = front;
    (*queue)->back = back;
    (*queue)->push = push;
    (*queue)->pop = pop;
    (*queue)->empty = empty;
    (*queue)->size = size;
    (*queue)->clear = clear;
    (*queue)->destory = destory;
}

static int push(queue queue, void *data, size_t size){
    int push_result = queue->list->push_back(queue->list, data, size);
    if (!push_result)
        queue->queue_size += 1;
    return push_result;
}

static int pop(queue queue){
    int pop_result = queue->list->pop_front(queue->list);
    if (!pop_result)
        queue->queue_size -= 1;
    return pop_result;
}

static size_t size(const queue queue){
    return queue->queue_size;
}

static int empty(const queue queue){
    if (queue->queue_size == 0)
        return 1;

    return 0;
}

static void *front(const queue queue){
    if (empty(queue))
        return NULL;
    return queue->list->front(queue->list);
}

static void *back(const queue queue){
    if (empty(queue))
        return NULL;
    return queue->list->back(queue->list);
}

static void clear(queue queue){
    while (!empty(queue))
        pop(queue);
}

static void destory(queue queue){
    queue->clear(queue);
    queue->list->destory(queue->list);
    free(queue);
}