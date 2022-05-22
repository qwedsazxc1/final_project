#ifndef STUDENT_H
#define STUDENT_H

#include "avl_tree.h"
#include "error.h"
#include "vector.h"
#include <stdio.h>
#include <time.h>

struct place_record{
    time_t time;
    int place_id;
};

typedef struct student *student;

struct student{
    int id;
    char name[30];
    vector path;
};

typedef struct student_list *student_list;

struct student_list{
    int student_amount;
    avl_tree student_tree;
};

void initial_student(student student);
void initial_student_list(student_list student_list);
#endif