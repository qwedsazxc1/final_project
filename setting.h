#ifndef SETTING_H
#define SETTING_H

#include <stdio.h>
#include <errno.h>
#include "error.h"
#include "lib.h"

extern int hot_spot_standard;
extern int default_year;
extern int default_month;
extern int default_day;
extern int default_hour;
extern int default_minute;
extern int default_second;

// return 0 if OK
// -1 if error
int read_from_setting();

// return 0 if OK
// -1 if error
void write_to_setting();

void change_setting();

void print_input_time_format();

#endif