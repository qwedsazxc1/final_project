#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <string.h>
#define ERROR_MESSAGE_LENGTH (100)

extern char error_message[ERROR_MESSAGE_LENGTH + 1];

// set the error message 
void set_error_message(const char *error);

// print the message
void print_error_message(void);

// set the error message and then print it
void set_and_print_error_message(const char *error);
#endif