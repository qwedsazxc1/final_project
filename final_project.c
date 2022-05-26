/*
    This is Chung-Cheng University Computer science and Information engineering course : program design(II)'s final project
    Group : 電神阿宏與他的小夥伴
    participant :
    student ID : 410410021, name : Yi-Hong Lin, mail : linyihong1234@gmail.com
    student ID : 410410083
    student ID : 410410011
    student ID : 410410067
    student ID : 410410080
*/

#include "avl_tree.h"
#include "error.h"
#include "lib.h"
#include "list.h"
#include "queue.h"
#include "stack.h"
#include "student.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE (4096)

void seg_fault(int signo);

int main(int argc, char *argv[]){
    char *input_buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
    if (signal(SIGSEGV, seg_fault) == SIG_ERR){
        set_and_print_error_message("signal error\n");
       	exit(0);
    }
    FILE *footprint = fopen("footprint.csv", "r");
    if (footprint == NULL){
        set_and_print_error_message("fopen fail : fail to open footprint.csv\n");
        exit(0);
    }
    free(input_buffer);
    return 0;
}

void seg_fault(int signo){
    set_and_print_error_message("Segmentation fault\n");
    exit(139);
}
