#include "vector.h"

static void push_back(vector vector, void *data);
static void pop_back(vector vector);
static int size(const vector vector);
static int empty(const vector vector);
static void clear(vector vector);
static void *front(const vector vector);
static void *back(const vector vector);
static void erase(vector vector, int index);
static void insert(vector vector, int index, void *data);

void initial_vector(vector *vector, size_t element_size, void (*destroy_data_function)(void *data)){

    // raise error message if allocation fails
    *vector = malloc(sizeof(struct vector));
    if (*vector == NULL){
        set_and_print_error_message("initialization error : memory allocation fail\n");
        return;
    }

    (*vector)->array = malloc(element_size * 10);
    if ((*vector)->array == NULL){
        set_and_print_error_message("initialization error : memory allocation fail\n");
        free(*vector);
        return;
    }
    
    // initializations
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
    (*vector)->erase = erase;
    (*vector)->insert = insert;
}

void destory_vector(vector *vector){
    free((*vector)->array);
    free(*vector);
    *vector = NULL;
}

static void push_back(vector vector, void *data){
    // realloc doubles the original memory size if vector is full
    if (vector->num_of_element == vector->max_size){
        void *temp_ptr = realloc(vector->array, vector->element_size * 2 * vector->num_of_element);

        // allocation fails
        if (temp_ptr == NULL){
            set_and_print_error_message("vector (push back) : memory allocation fail\n");
            return;
        }

        // reinitializations due to reallocation
        vector->array = temp_ptr;
        vector->max_size = 2 * vector->max_size;
    }

    // the push operation
    memcpy(((char *)vector->array + vector->element_size * vector->num_of_element), data, vector->element_size);
    vector->num_of_element += 1;
}

// pop the last element
static void pop_back(vector vector){
    if (vector->num_of_element <= 0)
        return;
    
    vector->num_of_element -= 1;
    vector->destroy_data_function((char *)vector->array + (vector->num_of_element * vector->element_size));
}

// return the size of the vector
static int size(const vector vector){
    return vector->num_of_element;
}

// check if the vector is empty
static int empty(const vector vector){
    return vector->num_of_element > 0;
}

// pop all elements until nothing left
static void clear(vector vector){
    while (!empty(vector))
        pop_back(vector);
}

// returns a pointer to the first element
static void *front(const vector vector){
    return vector->array;
}

// returns a pointer to the last element
static void *back(const vector vector){
    return ((char *)vector->array) + ((vector->num_of_element - 1) * vector->element_size);
}

static void erase(vector vector, int index){
    if (index >= vector->num_of_element || index < 0)
        return;

    int buffer_size = (vector->num_of_element - index - 1) * vector->element_size;
    void *buffer = malloc(buffer_size);
    if (buffer == NULL){
        set_and_print_error_message("vector (erase) : memory allocation fail\n");
        return;
    }

    vector->destroy_data_function(((char *)vector->array) + index * vector->element_size);
    memcpy(buffer, ((char *)vector->array) + (index + 1) * vector->element_size, buffer_size);
    memcpy(((char *)vector->array) + index * vector->element_size, buffer, buffer_size);
    free(buffer);
    vector->num_of_element -= 1;
}

static void insert(vector vector, int index, void *data){
    if (index >= vector->num_of_element || index < 0)
        return;

    int buffer_size = (vector->num_of_element - index) * vector->element_size;
    void *buffer = malloc(buffer_size);
    if (buffer == NULL){
        set_and_print_error_message("vector (insert) : memory allocation fail\n");
        return;
    }

    // realloc doubles the original memory size if vector is full
    if (vector->num_of_element == vector->max_size){
        void *temp_ptr = realloc(vector->array, vector->element_size * 2 * vector->num_of_element);

        // allocation fails
        if (temp_ptr == NULL){
            set_and_print_error_message("vector (insert) : memory allocation fail\n");
            free(buffer);
            return;
        }

        // reinitializations due to reallocation
        vector->array = temp_ptr;
        vector->max_size = 2 * vector->max_size;
    }

    memcpy(buffer, (char *)vector->array + index * vector->element_size, buffer_size);
    memcpy((char *)vector->array + index * vector->element_size, data, vector->element_size);
    memcpy((char *)vector->array + (index + 1) * vector->element_size, buffer, buffer_size);
    vector->num_of_element += 1;
    free(buffer);
}