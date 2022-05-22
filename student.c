#include "student.h"

int student_id_compare(const void *a, const void *b){
    const struct student *current_data = a;
    const struct student *target = b;
    return current_data->id - target->id;
}

void initial_student_list(student_list student_list){
    initial_avl_tree(&student_list->student_tree);
    student_list->student_amount = 0;
}

void add_student(student_list student_list, int student_id, const char *name){
    student target = malloc(sizeof(struct student));
    target->id = student_id;
    student student_data = student_list->student_tree->search(student_list->student_tree, target, student_id_compare);
    if (student_data != NULL){
        set_and_print_error_message("the student is already exist.\n");
        free(target);
        return;
    }
    strcpy(target->name, name);
    //initial_avl_tree(&target->path);
    student_list->student_tree->add(student_list->student_tree, target, sizeof(struct student), student_id_compare);
    free(target);
}

