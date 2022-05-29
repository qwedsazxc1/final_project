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

#include "avl_tree.h"
#include "error.h"
#include "lib.h"
#include "list.h"
#include "queue.h"
#include "stack.h"
#include "student.h"
#include "vector.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE (4096)

void seg_fault(int signo);

int main(int argc, char *argv[]){
    if (argc != 1 && argc != 2){
        printf("Usage : ./avl_tree_ver [file]\n");
        return 0;
    }
    char *input_buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
    /*if (signal(SIGSEGV, seg_fault) == SIG_ERR){
        set_and_print_error_message("signal error\n");
       	exit(0);
    }*/
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
    student_list student_list;
    initial_student_list(&student_list);
    if (fscanf(footprint, "time,student_id,place_id") == EOF){
        set_and_print_error_message("footprint.csv : read error\n");
        exit(0);
    }
    unsigned long long time;
    int student_id, place_id;
    while (fscanf(footprint, "%llu,%d,%d", &time, &student_id, &place_id) != EOF){
        add_student_path(student_list, student_id, place_id, time);
    }
    print_all_list(student_list);
    destory_student_list(student_list);
    free(input_buffer);
    return 0;
}

void seg_fault(int signo){
    set_and_print_error_message("Segmentation fault\n");
    exit(139);
}
