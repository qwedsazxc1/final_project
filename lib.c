#include <stdio.h>
#include "lib.h"

void swap(void *a, void *b, size_t size){
    unsigned char *first = a, *second = b, tmp;
    for (int i = 0; i < size; i++){
        tmp = first[i];
        first[i] = second[i];
        second[i] = tmp;
    }
}

void fflush_stdin(void){
    char c;
    while((c = getchar()) != EOF && c != '\n')
        ;
}