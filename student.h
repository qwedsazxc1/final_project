#ifndef STUDENT_H
#define STUDENT_H

#include "avl_tree.h"
#include "error.h"
#include "vector.h"
#include <stdio.h>
#include <time.h>

struct place_record{
    int student_id;
    time_t time;
    int place_id;
};

struct student{
    int id;
    char name[30];
    vector path;
};

struct student_list{
    int student_amount;
    avl_tree student_tree;
};

typedef struct place_record place_record;
typedef struct student_list *student_list;
typedef struct student *student;

void initial_student(student student);
void initial_student_list(student_list student_list);
void add_student(student_list student_list, int student_id, const char *name);
#endif