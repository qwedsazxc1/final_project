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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE (4096)

int main(int argc, char **argv){
    char *input_buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
    setvbuf(stdin, input_buffer, _IOLBF, BUFFER_SIZE);
    free(input_buffer);
    return 0;
}