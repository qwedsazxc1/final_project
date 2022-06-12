#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <stdio.h>
#include "lib.h"
#include <unistd.h>
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
extern char *delete_success_msg;

extern char *search_place_id1;
extern char *search_place_id2;
extern char *search_place_id3;
extern char *search_place_id4;
extern char *search_place_id5;
//////////////////////////////////////////////
extern char *change_setting1;
extern char *change_setting2;
extern char *change_setting3;
extern char *change_setting4;
extern char *change_setting5;
extern char *change_setting6;
extern char *change_setting7;

extern char *change_value;


extern char *change_date1;
extern char *change_date2;

extern char *default_is;

void choose_language();

void decide_message();

#endif