#include "student.h"

static void print_func(const void *data);
static void destory_data_function(void *data);
static void destory_student_data_function(void *data);

static int student_id_compare(const void *a, const void *b){
    const struct student *current_data = a;
    const struct student *target = b;
    return current_data->student_id - target->student_id;
}

void initial_student_list(student_list *student_list){
    *student_list = malloc(sizeof(struct student_list));
	//ensure the memories set is successfull
    if (*student_list == NULL){
        set_and_print_error_message("initial student list error : memory allocate fail\n");
        return;
    }
    initial_avl_tree(&((*student_list)->student_tree), student_id_compare, print_func, destory_student_data_function);
    (*student_list)->student_amount = 0;
}

void add_student(student_list student_list, int student_id){
    student target = malloc(sizeof(struct student));
	//ensure the memories set is successful
    if (target == NULL){
        set_and_print_error_message("add_student : memory alloate fail\n");
        return;
    }
    target->student_id = student_id;
    student student_data = student_list->student_tree->search(student_list->student_tree, target);
    if (student_data != NULL){
        set_and_print_error_message("the student is already exist.\n");
        free(target);
        return;
    }
    initial_vector(&(target->path), sizeof(place_record), destory_data_function);
    int add_result = student_list->student_tree->insert(student_list->student_tree, target, sizeof(struct student));
    if (add_result)
        set_and_print_error_message("some problem happen\n");
    free(target);
    student_list->student_amount += 1;
}

static void print_func(const void *data){
    const student student_data = (student)data;
    place_record *record = (place_record *)student_data->path->array;
    for (int i = 0; i < student_data->path->num_of_element; i++)
        printf("%d,%llu,%5d\n", record[i].student_id, (unsigned long long)record[i].time, record[i].place_id);
}

static void destory_student_data_function(void *data){
    student target = data;
    destory_vector(target->path);
}

static void destory_data_function(void *data){
    return;
}

void add_student_path(student_list student_list, int student_id, int place_id, time_t time){
    struct student search_target;
    search_target.student_id = student_id;
    student target = student_list->student_tree->search(student_list->student_tree, &search_target);
    if (target == NULL){
        add_student(student_list, student_id);
        target = student_list->student_tree->search(student_list->student_tree, &search_target);
    }
    place_record *data = malloc(sizeof(place_record));
    if  (data == NULL){
        set_and_print_error_message("add_student_path : memory allocate fail\n");
        return;
    }
    data->time = time;
    data->student_id = student_id;
    data->place_id = place_id;
    
    target->path->push_back(target->path, data);
    free(data);
}

void destory_student_list(student_list student_list){
    student_list->student_tree->clear(student_list->student_tree);
    free(student_list);
}

void print_all_student_list(student_list student_list){
    avl_tree_traversal(student_list->student_tree, IN_ORDER);
}
