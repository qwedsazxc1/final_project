#ifndef PLACE_H
#define PLACE_H

#include "lib.h"
#include "basic_data_structure/avl_tree.h"
#include "error.h"
#include "basic_data_structure/vector.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

#ifndef PLACE_RECORD
#define PLACE_RECORD
struct place_record{
    int student_id;
    time_t time;
    int place_id;
};

#endif

struct place{
    int place_id;
    vector path;
};

struct place_list{
    int place_amount;
    avl_tree place_tree;
};

typedef struct place_record place_record;
typedef struct place *place;
typedef struct place_list *place_list;

void initial_place_list(place_list *place_list);
void add_place(place_list place_list, int place_id);
void add_place_path(place_list place_list, int student_id, int place_id, time_t time);
void destory_place_list(place_list place_list);
void print_all_place_list(place_list place_list);
#endif