#ifndef STACK_H
#define STACK_H
#include "list.h"
#ifndef STACK_STRUCTURE
#define STACK_STRUCTURE
struct stack{
    struct list stack_list;
    size_t stack_size;
    int stack_top;
    int (*empty)(struct stack stack);
    int (*size)(struct stack stack);
    int (*top)(struct stack stack);
    int (*push)(struct stack *stack, int data);
    int (*pop)(struct stack *stack);
};
typedef struct stack stack;
#endif
void initial_stack(struct stack *stack);
#endif  