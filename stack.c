#include "stack.h"
static int empty(struct stack stack);
static int size(struct stack stack);
static int top(struct stack stack);
static int push(struct stack *stack, int data);
static int pop(struct stack *stack);

static int empty(struct stack stack){
    if (stack.stack_size == 0)
        return 1;
    return 0;
}

static int size(struct stack stack){
    return stack.stack_size;
}

static int top(struct stack stack){
    if (stack.stack_list.head != NULL)
        return stack.stack_list.head->data;

    return -1;
}

static int push(struct stack *stack, int data){
    int push_result = stack->stack_list.push_front(&(stack->stack_list), data);
    if (push_result == -1){
        set_and_print_error_message("stack : push element fail\n");
        return -1;
    }
    stack->stack_size += 1;
    stack->stack_top = stack->top(*stack);
    return 0;
}

static int pop(struct stack *stack){
    if (stack->empty(*stack)){
        set_and_print_error_message("stack : no element can pop\n");
        return 1;
    }
    stack->stack_list.pop_front(&(stack->stack_list));
    stack->stack_size -= 1;
    stack->stack_top = stack->top(*stack);
    return 0;
}

void initial_stack(struct stack *stack){
    stack->stack_size = 0;
    initial_double_linked_list(&(stack->stack_list));
    stack->stack_top = -1;
    stack->empty = empty;
    stack->size = size;
    stack->top = top;
    stack->push = push;
    stack->pop = pop;
}