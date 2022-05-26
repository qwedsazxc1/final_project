#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc != 4){
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
    fprintf(footprint_fp, "%s,%d,%d\n", argv[3], student_id, place_id);
    fclose(footprint_fp);
    return 0;
}
