#ifndef SETTING_H
#define SETTING_H
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#endif
#include <stdio.h>
#include <errno.h>
#include "error.h"
#include <time.h>
#include "lib.h"

#define SECOND 0 
#define MINUTE 1
#define HOUR 2
#define DAY 3
#define MONTH 4
#define YEAR 5

extern char default_date_string[50];
extern int hot_spot_standard;
extern struct tm default_date;

// return 0 if OK
// -1 if error
int read_from_setting();

// return 0 if OK
// -1 if error
void write_to_setting();

void change_setting();

void print_input_time_format();


#endif