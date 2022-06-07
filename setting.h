#ifndef SETTING_H
#define SETTING_H

#include <stdio.h>
#include <errno.h>
#include "error.h"
#include "lib.h"

extern unsigned long long hot_spot_standard;

// return 0 if OK
// -1 if error
int read_from_setting();

// return 0 if OK
// -1 if error
void write_to_setting();

void change_setting();

#endif