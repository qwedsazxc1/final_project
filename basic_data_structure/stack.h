#ifndef STACK_H
#define STACK_H
#include "list.h"
typedef struct stack *stack;
struct stack{
    list stack_list;
    size_t stack_size;
    void *stack_top;
    int (*empty)(const stack stack);
    int (*size)(const stack stack);
    void *(*top)(const stack stack);
    int (*push)(stack stack, void *data, size_t size);
    int (*pop)(stack stack);
    void (*clear)(stack stack);
    void (*destory)(stack stack);
};

void initial_stack(stack *stack, void (*destory_data_function)(void *data));
#endif  