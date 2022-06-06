#ifndef STACK_H
#define STACK_H
#include "list.h"
typedef struct stack *stack;
struct stack{
    list stack_list;
    size_t stack_size;
    void *stack_top;
    // check if the queue is empty
    int (*empty)(const stack stack);
    // return the size of stack
    int (*size)(const stack stack);
    // return the front
    void *(*top)(const stack stack);
    // return the front of stack list
    int (*push)(stack stack, void *data, size_t size);
    // pop an element at the front of the stack
    int (*pop)(stack stack);
    // pop all elements until nothing left
    void (*clear)(stack stack);
    // delete the current stack
    void (*destory)(stack stack);
};

void initial_stack(stack *stack, void (*destory_data_function)(void *data));
#endif  