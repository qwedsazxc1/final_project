#include "place.h"

static int place_id_cmp(const void *a, const void *b);
static void print_func(const void *data);
static void destory_place(void *data);
static void destory_data_function(void *data);

void initial_place_list(place_list *place_list){
    *place_list = malloc(sizeof(struct place_list));
    if (*place_list == NULL){
        set_and_print_error_message("initial place list : memory allocate fail\n");
        return;
    }
    (*place_list)->place_amount = 0;
    initial_avl_tree(&((*place_list)->place_tree), place_id_cmp, print_func, destory_place);
}

void add_place(place_list place_list, int place_id){
    place target = malloc(sizeof(struct place));
    if (target == NULL){
        set_and_print_error_message("add_place : memory alloate fail\n");
        return;
    }
    target->place_id = place_id;
    place student_data = place_list->place_tree->search(place_list->place_tree, target);
    if (student_data != NULL){
        set_and_print_error_message("the student is already exist.\n");
        free(target);
        return;
    }
    initial_vector(&(target->path), sizeof(place_record), destory_data_function);
    int add_result = place_list->place_tree->insert(place_list->place_tree, target, sizeof(struct place));
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

static void print_func(const void *data){
    const struct place *place_data = data;
    place_record *record = (place_record *)place_data->path->array;
    for (int i = 0; i < place_data->path->num_of_element; i++)
        printf("%d,%llu,%5d\n", record[i].student_id, (unsigned long long)record[i].time, record[i].place_id);
    
}

static void destory_place(void *data){
    struct place *place_data = data;
    destory_vector(&place_data->path);

}

static void destory_data_function(void *data){

}

void add_place_path(place_list place_list, int student_id, int place_id, time_t time){
    struct place search_target;
    search_target.place_id = place_id;
    place target = place_list->place_tree->search(place_list->place_tree, &search_target);
    if (target == NULL){
        add_place(place_list, place_id);
        target = place_list->place_tree->search(place_list->place_tree, &search_target);
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

void destory_place_list(place_list place_list){
    place_list->place_tree->clear(place_list->place_tree);
    free(place_list);
}

void print_all_place_list(place_list place_list){
    avl_tree_traversal(place_list->place_tree, IN_ORDER);
}