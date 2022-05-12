#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

typedef struct queue *queue;

struct queue{
    list list;
    size_t queue_size;
    void *(*front)(const queue queue);
    void *(*back)(const queue queue);
    int (*push)(queue queue, void *data, size_t size);
    int (*pop)(queue queue);
    size_t (*size)(const queue queue);
    int (*empty)(const queue queue);
    void (*clear)(queue queue);
    void (*destory)(queue queue);
};


void initial_queue(queue *queue);
#endif