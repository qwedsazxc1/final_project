#ifndef STACK_H
#define STACK_H
#include "list.h"
typedef struct stack *stack;
struct stack{
    list stack_list;
    size_t stack_size;
    int stack_top;
    int (*empty)(const stack stack);
    int (*size)(const stack stack);
    int (*top)(const stack stack);
    int (*push)(stack stack, int data);
    int (*pop)(stack stack);
    void (*clear)(stack stack);
};

void initial_stack(stack *stack);
#endif  