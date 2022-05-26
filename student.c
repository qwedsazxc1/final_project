#include "student.h"

static void print_func(const void *data);
static void destory_data_function(void *data);
static void destory_student_data_function(void *data);

static int student_id_compare(const void *a, const void *b){
    const struct student *current_data = a;
    const struct student *target = b;
    return current_data->id - target->id;
}

void initial_student_list(student_list *student_list){
    *student_list = malloc(sizeof(struct student_list));
    if (*student_list == NULL){
        set_and_print_error_message("initial student list error : memory allocate fail\n");
        return;
    }
    initial_avl_tree(&(*student_list)->student_tree, student_id_compare, print_func, destory_student_data_function);
    (*student_list)->student_amount = 0;
}

void add_student(student_list student_list, int student_id){
    student target = malloc(sizeof(struct student));
    target->id = student_id;
    student student_data = student_list->student_tree->search(student_list->student_tree, target);
    if (student_data != NULL){
        set_and_print_error_message("the student is already exist.\n");
        free(target);
        return;
    }
    initial_vector(&(target->path), sizeof(place_record), destory_data_function);
    student_list->student_tree->add(student_list->student_tree, target, sizeof(struct student));
    free(target);
}

static void print_func(const void *data){

}

static void destory_student_data_function(void *data){
    student target = data;
    destory_vector(target->path);
}

static void destory_data_function(void *data){
    return;
}

void record_path(student_list student_list, int student_id, int place_id){
    time_t current_time = time(NULL);
    student target = student_list->student_tree->search(student_list->student_tree, &student_id);
    if (target == NULL){
        add_student(student_list, student_id);
        target = student_list->student_tree->search(student_list->student_tree, &student_id);
    }
    place_record data;
    data.place_id = place_id;
    data.student_id = student_id;
    data.time = current_time;
    target->path->push_back(target->path, &data);
    char string_of_student_id[20], string_of_place_id[20], string_of_current_time[30];
    itoa_(student_id, string_of_student_id);
    itoa_(place_id, string_of_place_id);
    ultoa_((unsigned long long)current_time, string_of_current_time);
    char *command[] = {"./add", string_of_student_id, string_of_place_id, string_of_current_time, NULL};
    errno = 0;
    if (execvp("./add", command) == -1) {
        if (errno == EACCES)
            printf("[ERROR] permission is denied for a file\n");
        else
            perror("execvp");
        exit(EXIT_FAILURE);
    }
}