#include "queue.h"
static int front(const queue queue);
static int back(const queue queue);
static int push(queue queue, int data);
static int pop(queue queue);
static size_t size(const queue queue);
static int empty(const queue queue);
static void clear(queue queue);

void initial_queue(queue *queue){
    *queue = malloc(sizeof(struct queue));
    (*queue)->queue_size = 0;
    initial_double_linked_list(&(*queue)->list);
    (*queue)->front = front;
    (*queue)->back = back;
    (*queue)->push = push;
    (*queue)->pop = pop;
    (*queue)->empty = empty;
    (*queue)->size = size;
    (*queue)->clear = clear;
}

static int push(queue queue, int data){
    int push_result = queue->list->push_back(queue->list, data);
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

static int front(const queue queue){
    if (empty(queue))
        return -1;
    return queue->list->front(queue->list);
}

static int back(const queue queue){
    if (empty(queue))
        return -1;
    return queue->list->back(queue->list);
}

static void clear(queue queue){
    while (!empty(queue))
        pop(queue);
}