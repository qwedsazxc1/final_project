#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// prompting user of input format 
int main(int argc, char *argv[]){
    if (argc < 4 || argc > 6){
        printf("Usage : ./delete [student_id] [place_id] [time] [OPTION]\n");
        printf("option : \n");
        printf("-f, --file\t<arg>\tassign the file name that store information\n");
        return 0;
    }
    char file_name[85];
    char string_of_student_id[25] = {'\0'};
    char string_of_place_id[25] = {'\0'};
    char string_of_time[35] = {'\0'};
    strcpy(file_name, "footprint.csv");

    // fetch needed variables from argument vectors
    for (char **str = &argv[1]; *str != NULL; str++){
        if (strcmp("-f", *str) == 0 || strcmp("--file", *str) == 0){
            if (*(str++) == NULL)
                break;

            strncpy(file_name, *str, 80);
            continue;
        }
        if (string_of_student_id[0] == '\0'){
            strncpy(string_of_student_id, *str, 20);
            continue;
        }
        if (string_of_place_id[0] == '\0'){
            strncpy(string_of_place_id, *str, 20);
            continue;
        }
        if (string_of_time[0] == '\0'){
            strncpy(string_of_time, *str, 30);
            continue;
        }
    }

    // input format check
    if (atoi(string_of_student_id) < 1e8){
        fprintf(stderr, "student id format error\n");
        return 0;
    }
    if (atoi(string_of_place_id) <= 0){
        fprintf(stderr, "place id format error\n");
        return 0;
    }
    if (atoll(string_of_time) <= 0){
        fprintf(stderr, "time format error\n");
        return 0;
    }
    char *tmp_file_name = "temp_file.csv";

    // open files, raise error message when failsas, check file exist
    errno = 0;
    FILE *footprint_fp = fopen(file_name, "r");
    if (footprint_fp == NULL){
        fprintf(stderr, "file read error : cannot read file %s\n", file_name);
        perror("fopen");
        return 0;
    }
    errno = 0;
    FILE *footprint_write_fp = fopen(tmp_file_name, "w");
    if (footprint_write_fp == NULL){
        fprintf(stderr, "file write error : cannot write file %s\n", tmp_file_name);
        perror("fopen");
        return 0;
    }

    // delete_target format : time,student_id,place_id
    char input[100];
    char delete_target[100] = {'\0'};
    strncat(delete_target, string_of_time, 35);
    strcat(delete_target, ",");
    strncat(delete_target, string_of_student_id, 25);
    strcat(delete_target, ",");
    strncat(delete_target, string_of_place_id, 25);
    strcat(delete_target, "\n");

    int flag = 1;
    // pour everything to another file except "delete_target"
    while (fgets(input, 100, footprint_fp) != NULL){
        if (strcmp(delete_target, input) == 0){
            flag = 0;
            continue;
        }
        fprintf(footprint_write_fp, "%s", input);
    }
    if (flag)
        fprintf(stderr, "target not found\n");
    
    fclose(footprint_fp);
    fclose(footprint_write_fp);
    
    // update new footprint.csv
    remove(file_name);
    rename(tmp_file_name, file_name);
    return 0;
}