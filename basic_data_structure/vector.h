#ifndef VECTOR_H
#define VECTOR_H

#include "../error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector *vector;

struct vector{
    void *array;
    size_t num_of_element;
    size_t max_size;
    size_t element_size;
    void (*push_back)(vector vector, void *data);
    void (*pop_back)(vector vector);
    int (*empty)(const vector vector);
    int (*size)(const vector vector);
    void (*clear)(vector vector);
    void *(*front)(const vector vector);
    void *(*back)(const vector vector);
    void (*destroy_data_function)(void *data);
    void (*erase)(vector vector, int index);
    void (*insert)(vector vector, int index, void *data);
};

void destory_vector(vector *vector);
void initial_vector(vector *vector, size_t basic_type_size, void (*destroy_data_function)(void *data));

#endif