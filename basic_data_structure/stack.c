#include "stack.h"
// check if the queue is empty
static int empty(const stack stack);
// return the size of stack
static int size(const stack stack);
// return the front of stack list
static void *top(const stack stack);
// insert an element at the front of the stack
static int push(stack stack, void *data, size_t size);
// pop an element at the front of the stack
static int pop(stack stack);
// pop all elements until nothing left
static void clear(stack stack);
// delete the current stack
static void destory(stack stack);

void initial_stack(stack *stack, void (*destory_data_function)(void *data)){
    *stack = malloc(sizeof(struct stack));
    (*stack)->stack_size = 0;
    simple_initial_list(&(*stack)->stack_list, destory_data_function);
    (*stack)->stack_top = NULL;
    (*stack)->empty = empty;
    (*stack)->size = size;
    (*stack)->top = top;
    (*stack)->push = push;
    (*stack)->pop = pop;
    (*stack)->clear = clear;
    (*stack)->destory = destory;
}

static int empty(const stack stack){
    if (stack->stack_size == 0)
        return 1;
    return 0;
}

static int size(const stack stack){
    return stack->stack_size;
}

static void *top(const stack stack){
    if (empty(stack))
        return NULL;

    return stack->stack_list->front(stack->stack_list);
}

static int push(stack stack, void *data, size_t size){
    int push_result = stack->stack_list->push_front(stack->stack_list, data, size);
    if (push_result == -1){
        set_and_print_error_message("stack : push element fail\n");
        return -1;
    }
    stack->stack_size += 1;
    stack->stack_top = stack->top(stack);
    return 0;
}

static int pop(stack stack){
    if (stack->empty(stack)){
        set_and_print_error_message("stack : no element can pop\n");
        return 1;
    }
    stack->stack_list->pop_front(stack->stack_list);
    stack->stack_size -= 1;
    stack->stack_top = stack->top(stack);
    return 0;
}


static void clear(stack stack){
    while (!empty(stack))
        pop(stack);
}

static void destory(stack stack){
    stack->stack_list->destory(stack->stack_list);
    free(stack);
}