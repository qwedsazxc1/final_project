/*
    This is Chung-Cheng University Computer science and Information engineering course : program design(II)'s final project
    Group : 電神阿宏與他的小夥伴
    participant :
    student ID : 410410021, name : Yi-Hong Lin, mail : linyihong1234@gmail.com
    student ID : 410410083
    student ID : 410410011, name : Chao-Ting Wu, mail : justinwu105@gamil.com
    student ID : 410410067
    student ID : 410410080
*/

#include "basic_data_structure/list.h"
#include "error.h"
#include "lib.h"
#include "place.h"
#include "student.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUFFER_SIZE (4096)

char file_name[85];

void record_path(student_list student_list, place_list place_list, int student_id, int place_id);
void seg_fault(int signo);

int main(int argc, char *argv[]){
    if (argc != 1 && argc != 2){
        printf("Usage : ./avl_tree_ver [file]\n");
        return 0;
    }
    char *input_buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
    // error message raised when raised you attempt to illegally access or modify memory.
    if (signal(SIGSEGV, seg_fault) == SIG_ERR){
        set_and_print_error_message("signal error\n");
       	exit(0);
    }
    
    if (argc == 1)
        strcpy(file_name, "footprint.csv");
    else
        strncpy(file_name, argv[1], 80);
    errno = 0;
    FILE *footprint = fopen(file_name, "r");
    if (footprint == NULL){
        set_and_print_error_message("fopen fail : fail to open csv file\n");
        perror("fopen");
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
    //////////////////////////////////////////
    typedef unsigned long long ull;
    system("clear");
    printf("In this program, we will show the efficiency of avl tree compared with other data structures.\n");
    printf("Current version : Adelson-Velskii and Landis tree.\n");
    printf("Select options below to interact with database.\n");
    record_path(student_list, place_list, 410410021, 200);
    int options;
    _Bool flag = 0;
    while(1)
    {
        printf("-----------------------------\n");
        printf("0:End\n");
        printf("1:Search a student ID, the output will be students whose footprint overlaps \n");
        printf("2:Add new footprint to database.\n");
        printf("3:Delete a specific footprint.\n");
        printf("4:Campus hot spot analyze.\n");
        scanf("%d", &options);
        switch(options)
        {
            case 1:// search ID, print out overlapped studentID at what time, which place
                printf("Please type in student ID.\n");
                break;
            case 2:// add footprints
                printf("Input format : ID time place\n");
                break;
            case 3:// delete footprints
                printf("Input format : ID time place\n");
                break;
            case 4:
                // hotspot();
                break;
            case 0:
                flag = 1;
                break;
        }
        if(flag)
        {
            print_all_student_list(student_list);
            printf("-----------------------------\n");
            print_all_place_list(place_list);
            break;
        }

    }
    
    //////////////////////////////////////////
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
    pid_t pid;
    errno = 0;
    if ((pid = fork()) < 0){
        perror("fork");
        exit(1);
    }

    // child proccess
    if (pid == 0){
        char string_of_student_id[20], string_of_place_id[20], string_of_current_time[30];
        itoa_(student_id, string_of_student_id);
        itoa_(place_id, string_of_place_id);
        ultoa_((unsigned long long)current_time, string_of_current_time);
        char *command[] = {"./add", string_of_student_id, string_of_place_id, "-t", string_of_current_time, "-f", file_name, NULL};
        errno = 0;
        if (execvp("./add", command) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }

    // parent proccess
    int wstatus;
    errno = 0;
    if (waitpid(pid, &wstatus, 0) != pid){
        perror("wait");
        exit(1);
    }
}
