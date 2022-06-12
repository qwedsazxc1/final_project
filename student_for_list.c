#include "student_for_list.h"

// print the recorded student_id, time, and place_id
static int print_func(const void *data);

// must return it to avoid that it can't be free
static void destory_data_function(void *data);

// the function for free student data 
static void destory_student_data_function(void *data);

// compare the time and then use for avl sort
static int delete_compare(const void *a, const void *b);

// compare the student_id and then use for avl sort
static int student_id_compare(const void *a, const void *b){
    const struct student *current_data = a;
    const struct student *target = b;
    return current_data->student_id - target->student_id;
}

static int delete_compare(const void *a, const void *b){
    const struct place_record *current_data = a;
    const struct place_record *target = b;
    if (current_data->time > target->time)
        return 1;
    
    if (current_data->time < target->time)
        return -1;
    
    if (current_data->place_id != target->place_id){
        set_and_print_error_message("place id error\n");
        return -1;
    }
    return 0;
}

void initial_student_list(student_list_ptr *student_list){
    *student_list = malloc(sizeof(struct student_list));

	// ensure the memories set is successfull
    if (*student_list == NULL){
        set_and_print_error_message("initial student list error : memory allocate fail\n");
        return;
    }

    initial_list(&((*student_list)->student_list), destory_student_data_function, student_id_compare, print_func);
    (*student_list)->student_amount = 0;
}

void add_student(student_list_ptr student_list, int student_id){
    student target = malloc(sizeof(struct student));

	// ensure the memories set is successful
    if (target == NULL){
        set_and_print_error_message("add_student : memory alloate fail\n");
        return;
    }
    
    target->student_id = student_id;
    student student_data = student_list->student_list->search_node_from_head(student_list->student_list, target);
    if (student_data != NULL){
        set_and_print_error_message("the student is already exist.\n");
        free(target);
        return;
    }
    initial_vector(&(target->path), sizeof(place_record), destory_data_function);
    int add_result = student_list->student_list->push_back(student_list->student_list, target, sizeof(struct student));
    if (add_result)
        set_and_print_error_message("some problem happen\n");
    free(target);
    student_list->student_amount += 1;
}

static int print_func(const void *data){
    const student student_data = (student)data;
    place_record *record = (place_record *)student_data->path->array;
    for (int i = 0; i < student_data->path->num_of_element; i++)
        printf("%d,%llu,%5d\n", record[i].student_id, (unsigned long long)record[i].time, record[i].place_id);

    return 0;
}

static void destory_student_data_function(void *data){
    student target = data;
    destory_vector(&target->path);
}

static void destory_data_function(void *data){
    return;
}

void add_student_path(student_list_ptr student_list, int student_id, int place_id, time_t time){
    struct student search_target;
    search_target.student_id = student_id;
    student target = student_list->student_list->search_node_from_head(student_list->student_list, &search_target);
    if (target == NULL){
        add_student(student_list, student_id);
        target = student_list->student_list->search_node_from_head(student_list->student_list, &search_target);
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

int delete_student_path(student_list_ptr student_list, int student_id, int place_id, unsigned long long at_time){
    struct student search_target;
    search_target.student_id = student_id;
    student target = student_list->student_list->search_node_from_head(student_list->student_list, &search_target);
    if (target == NULL){
        set_and_print_error_message("delete student path : target not found\n");
        return -1;
    }

    place_record *data = malloc(sizeof(place_record));
    if  (data == NULL){
        set_and_print_error_message("delete student path : memory allocate fail\n");
        return -2;
    }
    data->place_id = place_id;
    data->student_id = student_id;
    data->time = at_time;
    void *array = target->path->array;
    int index = binary_search(array, data, target->path->num_of_element, target->path->element_size, delete_compare);
    if (index == -1){
        set_and_print_error_message("delete student path : target not found\n");
        return -1;
    }
    target->path->erase(target->path, index);
    return 0;
}

void destory_student_list(student_list_ptr student_list){
    student_list->student_list->clear(student_list->student_list);
    free(student_list->student_list);
    free(student_list);
}

void print_all_student_list(student_list_ptr student_list){
    student_list->student_list->print_list_from_head(student_list->student_list);
}
