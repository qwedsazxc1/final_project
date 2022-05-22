#ifndef VECTOR_H
#define VECTOR_H

#include "error.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct vector *vector;

struct vector{
    void *array;
    size_t num_of_element;
    size_t max_size;
    size_t element_size;
    void (*push_back)(vector vector, void *data);
    void (*pop_back)(vector vector, void (*destroy_data_function)(void *data));
    int (*empty)(vector vector);
    int (*size)(vector vector);
    void (*clear)(vector vector, void (*destroy_data_function)(void *data));
    void *(*front)(vector vector);
    void *(*back)(vector vector);
};

void destory_vector(vector vector, void (*destroy_data_function)(void *data));
void initial_vector(vector *vector, size_t basic_type_size);

#endif