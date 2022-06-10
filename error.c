#include <stdio.h>
#include <string.h>
#include "error.h"
char error_message[ERROR_MESSAGE_LENGTH + 1];

// set the error message
void set_error_message(const char *error){
    strncpy(error_message, error, ERROR_MESSAGE_LENGTH);
}

// print the message
void print_error_message(void){
    fprintf(stderr, "%s", error_message);
}

// set the error message and then print it
void set_and_print_error_message(const char *error){
    set_error_message(error);
    print_error_message();
}