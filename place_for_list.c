#include "place_for_list.h"

// compare place_id
static int place_id_cmp(const void *a, const void *b);

// print the recorded student_id, time and place_id
static int print_func(const void *data);

// destroy specific place
static void destory_place(void *data);

static void destory_data_function(void *data);

// compare the time and then use for avl sort
static int delete_compare(const void *a, const void *b);

// allocate memory for new place in tree and initialize the data
void initial_place_list(place_list_ptr *place_list){
    *place_list = malloc(sizeof(struct place_list));
    if (*place_list == NULL){
        set_and_print_error_message("initial place list : memory allocate fail\n");
        return;
    }
    (*place_list)->place_amount = 0;
    initial_list(&((*place_list)->place_list), destory_place, place_id_cmp, print_func);
}

static int delete_compare(const void *a, const void *b){
    const struct place_record *current_data = a;
    const struct place_record *target = b;
    if (current_data->time > target->time)
        return 1;
    
    if (current_data->time < target->time)
        return -1;
    
    if (current_data->student_id != target->student_id){
        set_and_print_error_message("student id error\n");
        return -1;
    }
    return 0;
}

// add place into the tree
void add_place(place_list_ptr place_list, int place_id){
    place target = malloc(sizeof(struct place));
    if (target == NULL){
        set_and_print_error_message("add_place : memory alloate fail\n");
        return;
    }
    target->place_id = place_id;
    place student_data = place_list->place_list->search_node_from_head(place_list->place_list, target);
    if (student_data != NULL){
        set_and_print_error_message("the student is already exist.\n");
        free(target);
        return;
    }
    initial_vector(&(target->path), sizeof(place_record), destory_data_function);
    int add_result = place_list->place_list->push_back(place_list->place_list, target, sizeof(struct place));
    if (add_result)
        set_and_print_error_message("some problem happen\n");
    free(target);
    place_list->place_amount += 1;
}


static int place_id_cmp(const void *a, const void *b){
    const struct place *current = a;
    const struct place *target = b;
    return current->place_id - target->place_id;
}

// print the recorded student_id, time and place_id
static int print_func(const void *data){
    const struct place *place_data = data;
    place_record *record = (place_record *)place_data->path->array;
    for (int i = 0; i < place_data->path->num_of_element; i++)
        printf("%d,%llu,%5d\n", record[i].student_id, (unsigned long long)record[i].time, record[i].place_id);
    
    return 0;
}

// destroy specific place
static void destory_place(void *data){
    struct place *place_data = data;
    destory_vector(&place_data->path);

}

static void destory_data_function(void *data){}

void add_place_path(place_list_ptr place_list, int student_id, int place_id, time_t time){
    struct place search_target;
    search_target.place_id = place_id;
    place target = place_list->place_list->search_node_from_head(place_list->place_list, &search_target);
    if (target == NULL){
        add_place(place_list, place_id);
        target = place_list->place_list->search_node_from_head(place_list->place_list, &search_target);
    }
    place_record *data = malloc(sizeof(place_record));
    if  (data == NULL){
        set_and_print_error_message("add_place_path : memory allocate fail\n");
        return;
    }
    data->time = time;
    data->student_id = student_id;
    data->place_id = place_id;
    
    target->path->push_back(target->path, data);
    free(data);
}

int delete_place_path(place_list_ptr student_list, int student_id, int place_id, unsigned long long at_time){
    struct place search_target;
    search_target.place_id = place_id;
    place target = student_list->place_list->search_node_from_head(student_list->place_list, &search_target);
    if (target == NULL){
        set_and_print_error_message("delete place path : target not found\n");
        return -1;
    }

    place_record *data = malloc(sizeof(place_record));
    if  (data == NULL){
        set_and_print_error_message("delete place path : memory allocate fail\n");
        return -2;
    }
    data->place_id = place_id;
    data->student_id = student_id;
    data->time = at_time;
    void *array = target->path->array;
    int index = binary_search(array, data, target->path->num_of_element, target->path->element_size, delete_compare);
    if (index == -1){
        set_and_print_error_message("delete place path : target not found\n");
        return -1;
    }
    target->path->erase(target->path, index);
    return 0;
}


void destory_place_list(place_list_ptr place_list){
    place_list->place_list->clear(place_list->place_list);
    free(place_list);
}

// print all the place list with avl tree
void print_all_place_list(place_list_ptr place_list){
    place_list->place_list->print_list_from_head(place_list->place_list);
}