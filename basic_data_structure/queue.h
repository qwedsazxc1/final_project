#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

typedef struct queue *queue;

struct queue{
    list list;
    size_t queue_size;
    //return the list at front of the queue
    void *(*front)(const queue queue);
    //return the list at back of the queue
    void *(*back)(const queue queue);
    //insert an element from the back of queue 
    int (*push)(queue queue, void *data, size_t size);
    //delete an element from head of queue
    int (*pop)(queue queue);
    //return the size of queue
    size_t (*size)(const queue queue);
    // check if the queue is empty
    int (*empty)(const queue queue);
    // pop all elements until nothing left
    void (*clear)(queue queue);
    // delete the current queue
    void (*destory)(queue queue);
};


void initial_queue(queue *queue, void (*destory_data_function)(void *data));
#endif