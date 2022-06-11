#ifndef STUDENT_H
#define STUDENT_H

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

struct student{
    int student_id;
    vector path;
};

struct student_list{
    int student_amount;
    avl_tree student_tree;
};

typedef struct place_record place_record;
typedef struct student_list *student_list_ptr;
typedef struct student *student;

int delete_student_path(student_list_ptr student_list, int student_id, int place_id, unsigned long long at_time);
void initial_student(student student);
void initial_student_list(student_list_ptr *student_list);
void add_student(student_list_ptr student_list, int student_id);
void add_student_path(student_list_ptr student_list, int student_id, int place_id, time_t current_time);
void destory_student_list(student_list_ptr student_list);
void print_all_student_list(student_list_ptr student_list);
#endif
