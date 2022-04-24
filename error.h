#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <string.h>
#define ERROR_MESSAGE_LENGTH (100)

extern char error_message[ERROR_MESSAGE_LENGTH + 1];
void set_error_message(const char *error);
void print_error_message(void);
void set_and_print_error_message(const char *error);

#endif