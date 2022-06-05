#ifndef LIB_H
#define LIB_H
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

// basic swap algo
void swap(void *a, void *b, size_t size);

// clears buffer
void fflush_stdin(void);

// realizing int to ascii string (in c)
void itoa_(int number, char *string);

// realizing unsigned long to ascii string (in c)
void ultoa_(unsigned long long number, char *string);

void clear_screen();

void sort(void *base, size_t num_of_element, size_t size_of_element, int (*compare_function)(const void *, const void *));
int binary_search(const void *base, void *target, size_t num_of_element, size_t size_of_element, int (*compare_function)(const void *, const void *));
int lower_bound(const void *base, void *target, size_t num_of_element, size_t size_of_element, int (*compare_function)(const void *, const void *));
int upper_bound(const void *base, void *target, size_t num_of_element, size_t size_of_element, int (*compare_function)(const void *, const void *));

#endif