#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

int main(int argc, char *argv[]){
    if (argc < 3 || argc > 4){
        printf("Usage : ./test_case_generator [number_of_test_case] [generate_file_name] ([parameter])\n");
        return 0;
    }

	srand(time(NULL));
	int number_of_test_case = atoi(argv[1]);
	if (number_of_test_case <= 0){
		fprintf(stderr, "test case amount can not less than 1\n");
		return 0;
	}
	int student_id_list[] = {
		#include "student_id_list.txt"
	};
	int student_id_list_size = 12000;
	unsigned long long current_time = time(NULL);

	errno = 0;
	FILE *generate_file_name = fopen(argv[2], "w");
	if (generate_file_name == NULL){
		perror("fopen");
		return 0;
	}

	fprintf(generate_file_name, "time,student_id,place_id\n");
	if(argc == 4){
		if(strcmp(argv[3],"-l") == 0){
			int a_random_place = rand() % 10000 + 1;
			int a_randon_student_id = student_id_list[rand() % student_id_list_size];
			for (unsigned long long i = 0; i < number_of_test_case; i++){
				fprintf(generate_file_name, "%llu,%d,%d\n", current_time + i - number_of_test_case, a_randon_student_id, a_random_place);
			}
		}
		else if(strcmp(argv[3],"-li") == 0){
			int a_randon_student_id = student_id_list[rand() % student_id_list_size];
			for (unsigned long long i = 0; i < number_of_test_case; i++){
				fprintf(generate_file_name, "%llu,%d,%d\n", current_time + i - number_of_test_case, a_randon_student_id, rand() % 10000 + 1);
			}
		}
		else if(strcmp(argv[3],"-lp") == 0){
			int a_random_place = rand() % 10000 + 1;
			for (unsigned long long i = 0; i < number_of_test_case; i++ ){
				fprintf(generate_file_name, "%llu,%d,%d\n", current_time + i - number_of_test_case, student_id_list[rand() % student_id_list_size], a_random_place);
			}
		}
		else{
			printf("parameter format: [-l] [-li] [-lp]");
			return 0;
		}
	}
	else{
		for (unsigned long long i = 0; i < number_of_test_case; i++){
			fprintf(generate_file_name, "%llu,%d,%d\n", current_time + i - number_of_test_case, student_id_list[rand() % student_id_list_size], rand() % 10000 + 1);
		}
	}	

	fclose(generate_file_name);
	return 0;
	
}
