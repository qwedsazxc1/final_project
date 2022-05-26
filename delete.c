#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (argc != 4){
        printf("Usage : ./delete [student_id] [place_id] [time]\n");
        return 0;
    }
    char *tmp_file_name = "temp_file.csv";
    FILE *footprint_fp = fopen("footprint.csv", "r");
    FILE *footprint_write_fp = fopen(tmp_file_name, "w");
    if (footprint_fp == NULL){
        fprintf(stderr, "footprint.csv : cannot read footprint.csv\n");
        fprintf(stderr, "please check the file name \"footprint.csv\"\n");
        return 0;
    }
    char input[100];
    char delete_target[100] = {'\0'};
    strncat(delete_target, argv[3], 30);
    strcat(delete_target, ",");
    strncat(delete_target, argv[1], 15);
    strcat(delete_target, ",");
    strncat(delete_target, argv[2], 15);
    strcat(delete_target, "\n");
    int flag = 1;
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
    remove("footprint.csv");
    rename(tmp_file_name, "footprint.csv");
    return 0;
}