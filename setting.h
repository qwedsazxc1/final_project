#ifndef SETTING_H
#define SETTING_H
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#endif
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <errno.h>
#include "error.h"
#include "language.h"
#include <time.h>
#include "lib.h"

#define SECOND_IN_A_MINUTE 60
#define SECOND_IN_A_DAY 86400

extern int search_front_minute;
extern int search_after_minute;
extern int search_front_date;
extern int search_after_date;
extern char default_date_string[50];
extern int hot_spot_standard;
extern struct tm default_date;

// return 0 if OK
// -1 if error
int read_from_setting();

void write_to_setting();

void change_setting();

void print_input_time_format();

unsigned long long get_time_lower_bound();

unsigned long long get_time_upper_bound();

time_t get_search_visited_time_lower_bound(time_t time);

time_t get_search_visited_time_upper_bound(time_t time);

#endif