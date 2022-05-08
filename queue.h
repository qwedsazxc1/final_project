#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

struct queue{
    struct list list;
    size_t queue_size;
    int (*front)(const struct queue *queue);
    int (*back)(const struct queue *queue);
    int (*push)(struct queue *queue, int data);
    int (*pop)(struct queue *queue);
    size_t (*size)(const struct queue *queue);
    int (*empty)(const struct queue *queue);
};
typedef struct queue queue;

void initial_queue(struct queue* queue);
#endif