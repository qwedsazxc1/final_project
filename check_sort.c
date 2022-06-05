#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("input format: [check_file] [number_of_test_case] [parameter]\n")
		return 0;
	}
	
	if(atoi(argv[1]) <= 0){
		printf("number_of_tset_can't_be_less_than_0\n")
		return 0;
	}
	
	int number_of_test_case = atoi(argv[1]);

	int student_id = 0, prev_student_id = 0;
	unsigned long long time = 0, prev_time = 0;
	int place_id = 0, prev_place_id = 0;
	//check time sort
	if(strcmp(argv[2], -t) == 0){
		for(int i = 0;i < number_of_test_case;i++){
			scanf("%d,%llu,%d\n", &student_id, &time, &place_id);
			if(i == 0){
				prev_time = time;
			}
			if(prev_time > time){
				printf("False\n");
				return 0;
			}
			prev_time = time;
		}
	}
	//check place_id sort
	else if(strcmp(argv[2], -p) == 0){
		for(int i = 0;i < number_of_test_case;i++){
			scanf("%d,%llu,%d\n", &student_id, &time, &place_id);
			if(i == 0){
				prev_place_id = place_id;
			}
			if(prev_place_id > place_id){
				printf("False\n");
				return 0;
			}
			prev_place_id = place_id;
		}

	}
	//check student_id sort
	else if(strcmp(argv[2], -i) == 0){
		for(int i = 0;i < number_of_test_case;i++){
			scanf("%d,%llu,%d\n", &student_id, &time, &place_id);
			if(i == 0){
				prev_student_id = student_id;
			}
			if(prev_student_id > student_id){
				printf("False\n");
				return 0;
			}
			prev_student_id = student_id;
		}

	}
	else return 0;
}

