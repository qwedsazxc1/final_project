/*
    This is Chung-cheng University Computer science and Information engineering course : program design(II)'s final project
    participant :
    student ID : 410410021, name : Yi-Hong Lin, mail : linyihong1234@gmail.com
    student ID : 410410083
    student ID : 410410011
    student ID : 410410067
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked_list.h"
#include "lib.h"
#include "error.h"
#define BUFFER_SIZE (4096)

int main(int argc, char **argv){
    char *input_buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
    char *input_user_name = (char *)malloc(100 * sizeof(char));
    char *input_password = (char *)malloc(100 * sizeof(char));
    fprintf(stdout, "Please input username:");
    fscanf(stdin, "%4096s", input_buffer);
    fflush_stdin();
    sscanf(input_buffer, "%100s", input_user_name);
    fprintf(stdout, "Please input password:");
    fscanf(stdin, "%4096s", input_buffer);
    fflush_stdin();
    sscanf(input_buffer, "%100s", input_password);
    FILE *user = fopen("user.txt", "r");
    if (user == NULL){
        set_and_print_error_message("open user.txt fail\n");
        return 0;
    }
    fgets(input_buffer, BUFFER_SIZE, user);
    char *user_name = (char *)malloc(100 * sizeof(char));
    char *password = (char *)malloc(100 * sizeof(char));
    sscanf(input_buffer, "username:%100s , password:%100s", user_name, password);
    if(strcmp(user_name, input_user_name) != 0 || strcmp(password, input_password) != 0){
        fprintf(stdout, "Wrong username or password\n");
        return 0;
    }

    fprintf(stdout, "Welcome database\n");
    free(input_user_name);
    free(input_password);
    free(user_name);
    free(password);
    fclose(user);
    free(input_buffer);
    return 0;
}