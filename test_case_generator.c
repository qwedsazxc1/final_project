#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Usage : ./test_case_generator [number_of_test_case] [generate_file_name]\n");
        return 0;
    }
    srand(time(NULL));
    int student_id_list[] = {
        #include "student_id_list.txt"
    };
    int student_id_list_size = 12000;
    unsigned long long current_time = time(NULL);
    FILE *generate_file_name = fopen(argv[2], "w");
    fprintf(generate_file_name, "time,student_id,place_id\n");
    int number_of_test_case = atoi(argv[1]);
    for (unsigned long long i = 0; i < number_of_test_case; i++){
        fprintf(generate_file_name, "%llu,%d,%d\n", current_time + i, student_id_list[rand() % student_id_list_size], rand() % 10000 + 1);
    }
    fclose(generate_file_name);
    return 0;
}