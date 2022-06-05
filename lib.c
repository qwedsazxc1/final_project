#include "lib.h"

static void quick_sort(void *base, int left, int right, size_t size_of_elements, int (*compare_function)(const void *, const void *));
static int partition(void *base, int left, int right, size_t size_of_elements, int (*cmp)(const void *, const void *));

void clear_screen(void){
    errno = 0;
    int system_call_result = system("clear");
    if (system_call_result){
        perror("system(\"clear\")");
        exit(EXIT_FAILURE);
    }
}

// basic swap algo
void swap(void *a, void *b, size_t size){
    unsigned char *first = a, *second = b, tmp;
    for (int i = 0; i < size; i++){
        tmp = first[i];
        first[i] = second[i];
        second[i] = tmp;
    }
}

// clears buffer
void fflush_stdin(void){
    char c;
    while((c = getchar()) != EOF && c != '\n')
        ;
}

// realizing int to ascii string (in c)
void itoa_(int number, char *string){
    sprintf(string, "%d", number);
}

// realizing unsigned long to ascii string (in c)
void ultoa_(unsigned long long number, char *string){
    sprintf(string, "%llu", number);
}

void sort(void *base, size_t num_of_element, size_t size_of_element, int (*compare_function)(const void *, const void *)){
    quick_sort(base, 0, num_of_element - 1, size_of_element, compare_function);
}

static void quick_sort(void *base, int left, int right, size_t size_of_elements, int (*compare_function)(const void *, const void *)){
    if (left < right){
        int axis = partition(base, left, right, size_of_elements, compare_function);
        quick_sort(base, left, axis - 1, size_of_elements, compare_function);
        quick_sort(base, axis + 1, right, size_of_elements, compare_function);
    }
}

int partition(void *base, int left, int right, size_t size_of_elements, int (*compare_function)(const void *, const void *)){
    int i = left; 
    int j;
    for (j = left; j < right; j++){ 
        if (compare_function(base + right * size_of_elements, base + j * size_of_elements) > 0){
            swap((char *)base + i * size_of_elements, (char *)base + j * size_of_elements, size_of_elements);
            i++;
        } 
    } 

    swap(base + i * size_of_elements, base + right * size_of_elements, size_of_elements); 
    return i; 
}

int binary_search(const void *base, void *target, size_t num_of_element, size_t size_of_element, int (*compare_function)(const void *, const void *)){
    int max = num_of_element - 1;
    int min = 0;
    int traget_index = -1;
    while (max >= min){
        int mid = (max - min) / 2 + min;
        if (compare_function((char *)base + mid * size_of_element, target) > 0){
            max = mid - 1;
            continue;
        }
        if (compare_function((char *)base + mid * size_of_element, target) < 0){
            min = mid + 1;
            continue;
        }
        traget_index = mid;
        break;
    }
    return traget_index;
}

int lower_bound(const void *base, void *target, size_t num_of_element, size_t size_of_element, int (*compare_function)(const void *, const void *)){
    int max = num_of_element - 1;
    int min = 0;
    int traget_index = -1;
    while (max >= min){
        int mid = (max - min) / 2 + min;
        if (compare_function((char *)base + mid * size_of_element, target) >= 0){
            traget_index = mid;
            max = mid - 1;
            continue;
        }
        min = mid + 1;   
    }
    return traget_index;
}

int upper_bound(const void *base, void *target, size_t num_of_element, size_t size_of_element, int (*compare_function)(const void *, const void *)){
    int max = num_of_element - 1;
    int min = 0;
    int traget_index = -1;
    while (max >= min){
        int mid = (max - min) / 2 + min;
        if (compare_function((char *)base + mid * size_of_element, target) <= 0){
            traget_index = mid;
            min = mid + 1;
            continue;
        }
        max = mid - 1;   
    }
    return traget_index;
}