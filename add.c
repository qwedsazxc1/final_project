#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]){
    // prompting users of input format 
    if (argc < 3 || argc > 7){
        printf("Usage : ./add [student id] [place id] [OPTION]\n");
        printf("options : \n");
        printf("-t, --time\t<arg>\tassign the time be stored\n");
        printf("-f, --file\t<arg>\tassign the file name that store information\n");
        return 0;
    }
    char string_of_time[30] = {'\0'};
    char file[80] = {'\0'};
    char string_of_student_id[20] = {'\0'};
    char string_of_place_id[20] = {'\0'};
    strcpy(file, "footprint.csv");

    // fetch needed variables from argument vectors
    for (char **str = &argv[1]; *str != NULL; str++){
        if (strcmp("-t", *str) == 0 || strcmp("--time", *str) == 0){
            if (*(++str) == NULL)
                break;
            
            strncpy(string_of_time, *str, 30);
            continue;
        }
        if (strcmp("-f", *str) == 0 || strcmp("--file", *str) == 0){
            if (*(++str) == NULL)
                break;
            
            strncpy(file, *str, 80);
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
    }
    // input format check
    int student_id = atoi(string_of_student_id);
    if (student_id < 1e8){
        fprintf(stderr, "student id : %d\n", student_id);
        fprintf(stderr, "student id format error\n");
        return 0;
    }
    int place_id = atoi(string_of_place_id);
    if (place_id <= 0){
        fprintf(stderr, "place id format error\n");
        return 0;
    }
    errno = 0;
    //open file and check
    FILE *footprint_fp = fopen(file, "r");
    if (footprint_fp == NULL){
        fprintf(stderr, "file error : cannot read file %s\n", file);
        perror("fopen");
        return 0;
    }
    //add all information of student into file and check format
    footprint_fp = freopen(file, "a", footprint_fp);
    if (footprint_fp == NULL){
        fprintf(stderr, "file error : cannot read file %s\n", file);
        perror("fopen");
        return 0;
    }
    unsigned long long time_be_stored;
    if (string_of_time[0] == '\0')
        time_be_stored = (unsigned long long)time(NULL);
    else
        time_be_stored = atoll(string_of_time);

    if (time_be_stored == 0){
        fprintf(stderr, "time format error\n");
        return 0;
    }
    fprintf(footprint_fp, "%llu,%d,%d\n", time_be_stored, student_id, place_id);
    fclose(footprint_fp);
    return 0;
}
