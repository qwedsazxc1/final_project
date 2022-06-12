#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <stdio.h>
#include "lib.h"

#define ENGLISH 1
#define CHINESE 2

extern int language;

extern char *welcome_message;
extern char *features_list;
extern char *option_err_msg;
extern char *seg_err_msg;
extern char *record_msg;
extern char *record_success;
extern char *delete_msg;
extern char *format_err_msg;
extern char *illegal_retrieval;
extern char *deletion_applied;
extern char *search_options;

extern char *search_student_id1;
extern char *search_student_id2;
extern char *search_student_id3;
extern char *invalid_id_err_msg;
extern char *no_record_err_msg ;
extern char *boundary_err_msg;
extern char *search_student_id4;
extern char *search_student_id5;
extern char *enter_continue;

extern char *student_id_msg;
extern char *place_id_msg;
extern char *time_msg;
extern char *visited_time_msg;

void choose_language();

void decide_message();

#endif