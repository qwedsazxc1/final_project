/*
    This is Chung-Cheng University Computer science and Information engineering course : program design(II)'s final project
    Group : 電神阿宏與他的小夥伴
    participant :
    student ID : 410410021, name : Yi-Hong Lin, mail : linyihong1234@gmail.com
    student ID : 410410083
    student ID : 410410011
    student ID : 410410067
    student ID : 410410080
*/

#include "error.h"
#include "lib.h"
#include "basic_data_structure/list.h"
#include "place.h"
#include "student.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE (4096)

void record_path(student_list student_list, place_list place_list, int student_id, int place_id);
void seg_fault(int signo);

int main(int argc, char *argv[]){
    if (argc != 1 && argc != 2){
        printf("Usage : ./avl_tree_ver [file]\n");
        return 0;
    }
    char *input_buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
    if (signal(SIGSEGV, seg_fault) == SIG_ERR){
        set_and_print_error_message("signal error\n");
       	exit(0);
    }
    char file_name[80];
    if (argc == 1)
        strcpy(file_name, "footprint.csv");
    else
        strcpy(file_name, argv[1]);
    FILE *footprint = fopen(file_name, "r");
    if (footprint == NULL){
        set_and_print_error_message("fopen fail : fail to open csv file\n");
        exit(0);
    }
    if (fscanf(footprint, "time,student_id,place_id") == EOF){
        set_and_print_error_message("footprint.csv : read error\n");
        exit(0);
    }
    student_list student_list;
    initial_student_list(&student_list);
    place_list place_list;
    initial_place_list(&place_list);
    unsigned long long time;
    int student_id, place_id;
    while (fscanf(footprint, "%llu,%d,%d", &time, &student_id, &place_id) != EOF){
        add_student_path(student_list, student_id, place_id, time);
        add_place_path(place_list, student_id, place_id, time);
    }
    print_all_student_list(student_list);
    printf("-----------------------------\n");
    print_all_place_list(place_list);
    destory_student_list(student_list);
    destory_place_list(place_list);
    free(input_buffer);
    return 0;
}

void seg_fault(int signo){
    set_and_print_error_message("Segmentation fault\n");
    exit(139);
}


void record_path(student_list student_list, place_list place_list, int student_id, int place_id){
    time_t current_time = time(NULL);
    add_student_path(student_list, student_id, place_id, current_time);
    add_place_path(place_list, student_id, place_id, current_time);
    char string_of_student_id[20], string_of_place_id[20], string_of_current_time[30];
    itoa_(student_id, string_of_student_id);
    itoa_(place_id, string_of_place_id);
    ultoa_((unsigned long long)current_time, string_of_current_time);
    char *command[] = {"./add", string_of_student_id, string_of_place_id, string_of_current_time, NULL};
    errno = 0;
    if (execvp("./add", command) == -1) {
        if (errno == EACCES)
            printf("[ERROR] permission is denied for a file\n");
        else
            perror("execvp");
        exit(EXIT_FAILURE);
    }
}