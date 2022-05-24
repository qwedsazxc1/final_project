#include "vector.h"

static void push_back(vector vector, void *data);
static void pop_back(vector vector);
static int size(vector vector);
static int empty(vector vector);
static void clear(vector vector);
static void *front(vector vector);
static void *back(vector vector);

void initial_vector(vector *vector, size_t element_size, void (*destroy_data_function)(void *data)){
    (*vector)->array = malloc(element_size * 10);
    if ((*vector)->array == NULL){
        set_and_print_error_message("initial vector error : memory allocate fail\n");
        return;
    }
    (*vector)->element_size = element_size;
    (*vector)->max_size = 10;
    (*vector)->num_of_element = 0;
    (*vector)->push_back = push_back;
    (*vector)->pop_back = pop_back;
    (*vector)->empty = empty;
    (*vector)->size = size;
    (*vector)->clear = clear;
    (*vector)->front = front;
    (*vector)->back = back;
    (*vector)->destroy_data_function = destroy_data_function;
}

void destory_vector(vector vector){
    clear(vector);
    free(vector);
    vector = NULL;
}

static void push_back(vector vector, void *data){
    if (vector->num_of_element == vector->max_size){
        void *temp_ptr = realloc(vector->array, vector->element_size * 2 * vector->num_of_element);
        if (temp_ptr == NULL){
            set_and_print_error_message("vector (push back) : memory allocation fail\n");
            return;
        }
        vector->array = temp_ptr;
        vector->max_size = 2 * vector->max_size;

    }
    memcpy((vector->array + vector->element_size * vector->num_of_element), data, vector->element_size);
    vector->num_of_element += 1;
}

static void pop_back(vector vector){
    if (vector->num_of_element <= 0)
        return;
    
    vector->num_of_element -= 1;
    vector->destroy_data_function(vector->array + (vector->num_of_element * vector->element_size));
}

static int size(vector vector){
    return vector->num_of_element;
}

static int empty(vector vector){
    return vector->num_of_element > 0;
}

static void clear(vector vector){
    while (!empty(vector))
        pop_back(vector);
}

static void *front(vector vector){
    return vector->array;
}

static void *back(vector vector){
    return vector->array + ((vector->num_of_element - 1) * vector->element_size);
}