#include <stdio.h>
#include "lib.h"
//basic swap algo
void swap(void *a, void *b, size_t size){
    unsigned char *first = a, *second = b, tmp;
    for (int i = 0; i < size; i++){
        tmp = first[i];
        first[i] = second[i];
        second[i] = tmp;
    }
}
//clears buffer
void fflush_stdin(void){
    char c;
    while((c = getchar()) != EOF && c != '\n')
        ;
}
//realizing int to ascii string (in c)
void itoa_(int number, char *string){
    string[0] = '0';
    string[1] = '\0';
    int i = 0, sign = number;
    if (sign < 0){
        number *= -1;
        string[i++] = '-';
    }


    while (number){
        string[i++] = '0' + number % 10;
        number /= 10;
    }
    string[i] = '\0';
    if (sign > 0)
        for (int j = 0; j < i / 2; j++){
            swap(string + j, string + i - j - 1, sizeof(char));
        }
    else
        for (int j = 1; j < i / 2; j++){
            swap(string + j, string + i - j, sizeof(char));
        }
}
//realizing unsigned long to ascii string (in c)
void ultoa_(unsigned long long number, char *string){
    int i = 0;
    string[0] = '0';
    string[1] = '\0';
    while (number){
        string[i++] = '0' + number % 10;
        number /= 10;
    }
    string[i] = '\0';
    for (int j = 0; j < i / 2; j++){
        swap(string + j, string + i - j - 1, sizeof(char));
    }
}