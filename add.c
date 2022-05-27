#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc != 4 && argc != 3){
        fprintf(stdout, "Usage : add [student_id] [place_id] [time]\n");
        return 0;
    }
    FILE *footprint_fp = fopen("footprint.csv", "a");
    if (footprint_fp == NULL){
        fprintf(stderr, "footprint.csv : cannot read footprint.csv\n");
        fprintf(stderr, "please check the file name \"footprint.csv\"\n");
        return 0;
    }
    int student_id = atoi(argv[1]);
    if (student_id < 1e8){
        fprintf(stderr, "student id format error\n");
        return 0;
    }
    int place_id = atoi(argv[2]);
    if (place_id <= 0){
        fprintf(stderr, "place id format error\n");
        return 0;
    }
    unsigned long long current_time;
    if (argc == 3) 
        current_time = (unsigned long long)time(NULL);
    else
        current_time = atoll(argv[3]);
    
    if (current_time == 0){
        fprintf(stderr, "time format error\n");
        return 0;
    }
    fprintf(footprint_fp, "%llu,%d,%d\n", current_time, student_id, place_id);
    fclose(footprint_fp);
    return 0;
}
