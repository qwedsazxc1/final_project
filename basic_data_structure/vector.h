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
    //push another vector
    void (*push_back)(vector vector, void *data);
    // pop the last element
    void (*pop_back)(vector vector);
    // check if the vector is empty
    int (*empty)(const vector vector);
    // return the size of the vector
    int (*size)(const vector vector);
    // pop all elements until nothing left
    void (*clear)(vector vector);
    // returns a pointer to the first element
    void *(*front)(const vector vector);
    // returns a pointer to the last element
    void *(*back)(const vector vector);
    void (*destroy_data_function)(void *data);
    //delete an element
    void (*erase)(vector vector, int index);
    //insert an element
    void (*insert)(vector vector, int index, void *data);
};

void destory_vector(vector *vector);
void initial_vector(vector *vector, size_t basic_type_size, void (*destroy_data_function)(void *data));

#endif