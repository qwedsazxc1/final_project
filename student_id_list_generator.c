#include <stdio.h>
#include <errno.h>
#define FRONT 1000000
#define MIDDLE 1000

int main(){
    errno = 0;
    FILE *student_id = fopen("student_id_list.txt", "w");
    if (student_id == NULL){
        perror("fopen");
        return 0;
    }

    
    // the student_id will be constructed with three part: front, middle and k(1~100) 
    long long front[] = {407, 408, 409, 410};
    long long middle[30] = {110, 115, 120, 125, 210, 220, 235, 257, 260, 310, 315, 320, 330, 335, 410, 415, 420, 425, 430, 510, 515, 520,
                    526, 530, 610, 620, 630, 710, 725, 736};
    int front_size = 4;
    int middle_size = 30;
    for (int i = 0; i < front_size; i++){
        for (int j = 0; j < middle_size; j++){
            for (int k = 1; k <= 100; k++){
                long long id = FRONT * front[i] + middle[j] * MIDDLE + k;
                if (i == front_size - 1 && j ==  middle_size - 1 && k == 100)//the last student_id
                    fprintf(student_id, "%lld", id);
                else
                    fprintf(student_id, "%lld, ", id);
            }
            fprintf(student_id, "\n");
        }
    }
    fclose(student_id);
    return 0;
}
