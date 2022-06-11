/*
    This is Chung-Cheng University Computer science and Information engineering course : program design(II)'s final project
    Group : 電神阿宏與他的小夥伴
    participant :
    student ID : 410410021, name : Yi-Hong Lin, mail : linyihong1234@gmail.com
    student ID : 410410083
    student ID : 410410011, name : Chao-Ting Wu, mail : justinwu105@gmail.com
    student ID : 410410067, name : Jing-Yao Chan, mail : 
    student ID : 410410080, name : Hung-Che Huang, mail : huanghungche0615@gmail.com
*/
#define _GNU_SOURCE             

#include "basic_data_structure/list.h"
#include "error.h"
#include "lib.h"
#include "place.h"
#include "setting.h"
#include "student.h"
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define NOTHING 0
#define ENGLISH 1
#define CHINESE 0
#define RECORD 2
#define LEAVE 0
#define DELETE 3
#define HOT_SPOTS 4
#define SEARCH 1
#define SETTING 5
#define STUDENT_ORDER 1
#define PLACE_ORDER 2

typedef unsigned long long ull;

struct hot_spot{
    int place_id;
    unsigned long long number_of_people;
};
vector hot_spot_list = NULL;

struct place_list *place_list;
struct student_list *student_list;
int print_out = NOTHING;
char file_name[85];
int language;

void print_out_potential_contacts(place_record *record);
void search_student_id();
void print_out_check();
void initial(int argc, char *argv[]);
void deal_with_argv(int argc, char *argv[]);
void delete_path(int student_id, int place_id, unsigned long long at_time);
void clear_hot_spot();
int hot_spot_compare_function(const void *front, const void *back);
int time_compare_function(const void *front, const void *back);
void hot_spot_visited_function(const void *data);
void unused_function(void *data){}
void search();
void add_new_footprint();
void record_path(int student_id, int place_id);
void seg_fault(int signo);
void hot_spots();
void record();
void delete();
void clear_list();
void build_list();
void print_usage();
void search_place_id();

int main(int argc, char *argv[]){
    initial(argc, argv);

    print_out_check();
    clear_screen();
    printf("In this program, we will show the efficiency of avl tree compared with other data structures.\n");
    printf("Current version : Adelson-Velskii and Landis tree.\n");
    printf("Select options below to interact with database.\n");
    printf("Press Enter to continue\n");
    fflush_stdin();
    clear_screen();
    int options;
    while(1){
        printf("-----------------------------\n");
        printf("[0] : End\n");
        printf("[1] : Search a student ID, the output will be students whose footprint overlaps \n");
        printf("[2] : Add new footprint to database.\n");
        printf("[3] : Delete a specific footprint.\n");
        printf("[4] : Campus hot spot analyze.\n");
        printf("[5] : Setting\n");

        int input_result = scanf("%2d", &options);
        fflush_stdin();
        clear_screen();
        if (input_result != 1){    
            printf("invalid options\n");
            continue;
        }


        if (options == LEAVE)
            break;
        
        // search ID, print out overlapped studentID at what time, which place
        if (options == SEARCH){
            search(student_list, place_list);
            continue;
        }

        if (options == RECORD){
            record(student_list, place_list);
            continue;
        }

        // delete footprints
        if (options == DELETE){
            delete(student_list, place_list);
            continue;
        }

        if (options == HOT_SPOTS){
            hot_spots(place_list);
            continue;
        }

        if (options == SETTING){
            change_setting();
            continue;
        }

        printf("invalid options\n");
    }
    
    return 0;
}

void seg_fault(int signo){
    set_and_print_error_message("Segmentation fault\n");
    exit(139);
}

void record_path(int student_id, int place_id){
    time_t current_time = time(NULL);
    add_student_path(student_list, student_id, place_id, current_time);
    add_place_path(place_list, student_id, place_id, current_time);
    pid_t pid;
    errno = 0;
    if ((pid = fork()) < 0){
        perror("fork");
        exit(1);
    }

    // child proccess
    if (pid == 0){
        char string_of_student_id[20], string_of_place_id[20], string_of_current_time[30];
        itoa_(student_id, string_of_student_id);
        itoa_(place_id, string_of_place_id);
        ultoa_((unsigned long long)current_time, string_of_current_time);
        char *command[] = {"./add", string_of_student_id, string_of_place_id, "-t", string_of_current_time, "-f", file_name, NULL};
        errno = 0;
        if (execvp("./add", command) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }

    // parent proccess
    int wstatus;
    errno = 0;
    if (waitpid(pid, &wstatus, 0) != pid){
        perror("waitpid");
        exit(1);
    }
}

void search(){
    while (1){
        int option;
        printf("[0] : leave\n");
        printf("[1] : 「重疊捕獲者」 : search student ID, 跑出(誰)在(該日甚麼時間)在(哪裡)足跡重疊。\n");
        printf("[2] : 「健康檢測」 : search place ID, 跑出日期範圍內的紀錄\n");
        int input_result = scanf("%2d", &option);
        fflush_stdin();
        clear_screen();
        // check if scanf returns legitimate value
        if (input_result != 1){
            printf("Invalid option\n");
            continue;
        }
        // option mode
        if (option == 0)
            break;
        if (option == 1){

            search_student_id();
            continue;
        }
        if (option == 2){
            search_place_id();
            continue;
        }
        printf("Invalid option\n");
    }
}

void hot_spots(){
    if (hot_spot_list == NULL)
        initial_vector(&hot_spot_list, sizeof(struct hot_spot), unused_function);
    
    void (*temp_function_pointer)(const void *data) = place_list->place_tree->print_func;
    place_list->place_tree->print_func = hot_spot_visited_function;
    avl_tree_traversal(place_list->place_tree, IN_ORDER);
    place_list->place_tree->print_func = temp_function_pointer;

    sort(hot_spot_list->array, hot_spot_list->num_of_element, hot_spot_list->element_size, hot_spot_compare_function);
    struct hot_spot *array = hot_spot_list->array;
    for (int i = 0; i < hot_spot_list->num_of_element; i++){
        if (array[i].number_of_people < hot_spot_standard)
            break;
        printf("place ID : %5d, visited time : %10llu\n", array[i].place_id, array[i].number_of_people);
    }
    printf("Press Enter to continue\n");
    fflush_stdin();
    clear_screen();
}

void record(){
    int input_student_id, input_place_id;
    while (1){
        int input_result;
        printf("Please input student ID and place ID you want to record\n");
        printf("Input format : [student ID] [place ID]\n");
        printf("(input 0 if you want to leave)\n");
        printf("Input : ");
        input_result = scanf("%9d", &input_student_id);

        if (input_result != 1){
            fflush_stdin();
            clear_screen();
            printf("Input format error\n");
            continue;
        }

        if (input_student_id == LEAVE){
            fflush_stdin();
            clear_screen();
            break;
        }

        input_result = scanf("%9d", &input_place_id);
        fflush_stdin();
        clear_screen();
        if (input_result != 1){
            printf("Input format error\n");
            continue;
        }

        if (input_student_id  <= 1e8 || input_place_id <= 0 || input_place_id > 10000){
            printf("student ID or place ID error\n");
            continue;
        }

        record_path(input_student_id, input_place_id);
        printf("record success !\n");
    }
}

void hot_spot_visited_function(const void *data){
    const struct place *place_data = data;
    struct hot_spot hot_spot_data;
    hot_spot_data.place_id = place_data->place_id;
    hot_spot_data.number_of_people = (unsigned long long)place_data->path->num_of_element;
    hot_spot_list->push_back(hot_spot_list, &hot_spot_data);
}

void clear_hot_spot(){
    if (hot_spot_list != NULL)
        destory_vector(&hot_spot_list);
}

int hot_spot_compare_function(const void *front, const void *back){
    const struct hot_spot *front_h = front;
    const struct hot_spot *back_h = back;

    if (front_h->number_of_people == back_h->number_of_people)
        return front_h->place_id > back_h->place_id;
    

    if (front_h->number_of_people > back_h->number_of_people)
        return 0;

    return 1;
}

void delete(){
    int input_student_id, input_place_id;
    unsigned long long input_time;
    while (1){
        int input_result;
        printf("Please input the data you want to delete\n");
        printf("Input format : [student ID] [place ID] [target time]\n");
        printf("(input 0 if you want to leave)\n");
        printf("Input : ");
        input_result = scanf("%9d", &input_student_id);

        if (input_result != 1){
            fflush_stdin();
            clear_screen();
            printf("Input format error\n");
            continue;
        }

        if (input_student_id == LEAVE){
            fflush_stdin();
            clear_screen();
            break;
        }

        input_result = scanf("%9d%31llu", &input_place_id, &input_time);
        fflush_stdin();
        clear_screen();
        if (input_result != 2){
            printf("Input format error\n");
            continue;
        }

        if (input_student_id  <= 1e8 || input_place_id <= 0 || input_place_id > 10000){
            printf("Illegal data retrival\n");
            continue;
        }
        delete_path(input_student_id, input_place_id, input_time);
        printf("deletion applied !\n");
    }
}

void delete_path(int student_id, int place_id, unsigned long long at_time){
    delete_student_path(student_list, student_id, place_id, at_time);
    delete_place_path(place_list, student_id, place_id, at_time);
    pid_t pid;
    errno = 0;
    if ((pid = fork()) < 0){
        perror("fork");
        exit(1);
    }

    // child proccess
    if (pid == 0){
        char string_of_student_id[20], string_of_place_id[20], string_of_current_time[30];
        itoa_(student_id, string_of_student_id);
        itoa_(place_id, string_of_place_id);
        ultoa_(at_time, string_of_current_time);
        char *command[] = {"./delete", string_of_student_id, string_of_place_id, string_of_current_time, "-f", file_name, NULL};
        errno = 0;
        if (execvp("./delete", command) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }

    // parent proccess
    int wstatus;
    errno = 0;
    if (waitpid(pid, &wstatus, 0) != pid){
        perror("wait");
        exit(1);
    }
}

void clear_list(){
    destory_student_list(student_list);
    destory_place_list(place_list);
}

void build_list(){
    errno = 0;
    FILE *footprint = fopen(file_name, "r");
    if (footprint == NULL){
        set_and_print_error_message("fopen fail : fail to open csv file\n");
        perror("fopen");
        exit(0);
    }

    if (fscanf(footprint, "time,student_id,place_id") == EOF){
        set_and_print_error_message("csv file : read error\n");
        exit(0);
    }
    initial_student_list(&student_list);
    initial_place_list(&place_list);
    unsigned long long time;
    int student_id, place_id;
    while (fscanf(footprint, "%llu,%d,%d", &time, &student_id, &place_id) != EOF){
        add_student_path(student_list, student_id, place_id, time);
        add_place_path(place_list, student_id, place_id, time);
    }
}

void deal_with_argv(int argc, char *argv[]){
    if (argc < 1 && argc > 4){
        print_usage();
        exit(0);
    }
    strcpy(file_name, "footprint.csv");
    for (char **option = argv + 1; *option != NULL; option++){
        if (strcmp("-f", *option) == 0 || strcmp("--file", *option) == 0){
            if (*(++option) != NULL){
                strncpy(file_name, *option, 80);
                continue;
            }
            break;
        }
        if (strcmp("-ps", *option) == 0 || strcmp("--printstu", *option) == 0){
            print_out = STUDENT_ORDER;
            continue;
        }
        if (strcmp("-pp", *option) == 0 || strcmp("--printpla", *option) == 0){
            print_out = PLACE_ORDER;
            continue;
        }
        if (strcmp("-h", *option) == 0 || strcmp("--help", *option) == 0){
            print_usage();
            exit(0);
        }
        printf("unknown option : %s\n", *option);
        print_usage();
        exit(0);
    }
}

void initial(int argc, char *argv[]){
    deal_with_argv(argc, argv);

    errno = 0;
    if (atexit(clear_hot_spot)){
        perror("atexit");
        exit(0);
    }

    if (atexit(write_to_setting)){
        perror("atexit");
        exit(0);
    }


    // error message raised when raised you attempt to illegally access or modify memory.
    if (signal(SIGSEGV, seg_fault) == SIG_ERR){
        set_and_print_error_message("signal error\n");
       	exit(0);
    }

    int read_setting_status = read_from_setting();
    if (read_setting_status)
        exit(1);
    
    build_list();

    if (atexit(clear_list)){
        perror("atexit");
        exit(0);
    }

}

void print_out_check(){
    if (print_out == STUDENT_ORDER){
        print_all_student_list(student_list);
        exit(0);
    }
    if (print_out == PLACE_ORDER){
        print_all_place_list(place_list);
        exit(0);
    }
}

void print_(){
    printf("Usage : ./avl_tree_ver [option]\n");
    printf("option :\n");
    printf("-f, --file <csv file>\t, load informtaion from csv file \n");
    printf("-ps, --printstu\tprint output sort by student id\n");
    printf("-pp, --printpla\tprint output sort by place id\n");
    return;
}

void search_student_id(){
    while(1){
        unsigned long long time_lower_bound = get_time_lower_bound();
        unsigned long long time_upper_bound = get_time_upper_bound();
        char time_lower_bound_string[50]; 
        char time_upper_bound_string[50]; 
        strftime(time_lower_bound_string, 40, "%Y-%m-%d", gmtime((time_t *)&time_lower_bound));
        strftime(time_upper_bound_string, 40, "%Y-%m-%d", gmtime((time_t *)&time_upper_bound));
        printf("search region : from %s to %s\n", time_lower_bound_string, time_upper_bound_string);
        printf("(include head and tail)\n");
        printf("input 0 if you want to leave\n");
        printf("please input student ID\n");
        int input_student_id;
        int input_result = scanf("%9d", &input_student_id);
        fflush_stdin();
        clear_screen();
        if (input_result != 1){
            printf("invalid student ID\n");
            continue;
        }

        if (input_student_id == 0)
            break;
        
        struct student search_target;
        search_target.student_id = input_student_id;
        student search_result;
        search_result = student_list->student_tree->search(student_list->student_tree, &search_target);
        if (search_result == NULL){
            printf("invalid student ID\n");
            continue;
        }

        place_record lower_bound_target;
        lower_bound_target.time = time_lower_bound;
        int lower_bound_index = lower_bound(search_result->path->array, &lower_bound_target, search_result->path->num_of_element \
        , search_result->path->element_size, time_compare_function);

        place_record upper_bound_target;
        upper_bound_target.time = time_upper_bound;
        int upper_bound_index = upper_bound(search_result->path->array, &upper_bound_target, search_result->path->num_of_element \
        , search_result->path->element_size, time_compare_function);

        if (lower_bound_index == -1 || upper_bound_index == -1){
            printf("no record\n");
            continue;
        }

        if (lower_bound_index > upper_bound_index){
            printf("lower bound greater than upper bound\n");
            continue;
        }

        printf("Student ID : %d visited record\n", search_result->student_id);
        printf("\n");
        for (int i = lower_bound_index; i <= upper_bound_index; i++){
            print_out_potential_contacts((place_record *)search_result->path->array + i);
            printf("\n");
        }
        printf("Press Enter to continue...\n");
        fflush_stdin();
        clear_screen();
        break;
    }
}

int time_compare_function(const void *front, const void *back){
    const struct place_record *front_record = front;
    const struct place_record *back_record = back;
    return front_record->time - back_record->time;
}

void print_out_potential_contacts(place_record *record){
    char visited_time_string[50];
    strftime(visited_time_string, 40, "%Y-%m-%d %H:%M:%S", gmtime(&(record->time)));
    printf("time : %s, place : %d\n", visited_time_string, record->place_id);
    time_t search_visited_time_lower_bound = get_search_visited_time_lower_bound(record->time);
    time_t search_visited_time_upper_bound = get_search_visited_time_upper_bound(record->time);

    struct place place_target;
    place_target.place_id = record->place_id;
    struct place *place_search_reult = place_list->place_tree->search(place_list->place_tree, &place_target);
    if (place_search_reult == NULL){
        set_and_print_error_message("print_out_potential_contacts : can not find place record\n");
        return;
    }

    place_record visited_time_lower_bound_target;
    visited_time_lower_bound_target.time = search_visited_time_lower_bound;
    int search_visited_time_lower_bound_index = lower_bound(place_search_reult->path->array, &visited_time_lower_bound_target, \
    place_search_reult->path->num_of_element, place_search_reult->path->element_size, time_compare_function);

    place_record visited_time_upper_bound_target;
    visited_time_upper_bound_target.time = search_visited_time_upper_bound;
    int search_visited_time_upper_bound_index = upper_bound(place_search_reult->path->array, &visited_time_upper_bound_target, \
    place_search_reult->path->num_of_element, place_search_reult->path->element_size, time_compare_function);

    if (search_visited_time_upper_bound_index == -1 || search_visited_time_lower_bound_index == -1){
        printf("no record\n");
        return;
    }

    if (search_visited_time_lower_bound_index > search_visited_time_upper_bound_index){
        printf("lower bound greater than upper bound\n");
        return;
    }

    for (int i = search_visited_time_lower_bound_index; i <= search_visited_time_upper_bound_index; i++){
        strftime(visited_time_string, 40, "%Y-%m-%d %H:%M:%S", gmtime(&(((place_record *)place_search_reult->path->array)[i].time)));
        printf("time : %s, student ID : %d\n", visited_time_string, ((place_record *)place_search_reult->path->array)[i].student_id);
    }
}

void search_place_id(){
    while (1){
        unsigned long long time_lower_bound = get_time_lower_bound();
        unsigned long long time_upper_bound = get_time_upper_bound();
        char time_lower_bound_string[50]; 
        char time_upper_bound_string[50]; 
        strftime(time_lower_bound_string, 40, "%Y-%m-%d", gmtime((time_t *)&time_lower_bound));
        strftime(time_upper_bound_string, 40, "%Y-%m-%d", gmtime((time_t *)&time_upper_bound));
        printf("search region : from %s to %s\n", time_lower_bound_string, time_upper_bound_string);
        printf("(include head and tail)\n");
        printf("input 0 if you want to leave\n");
        printf("please input place ID\n");
        int input_place_id;
        int input_result = scanf("%d", &input_place_id);
        fflush_stdin();
        clear_screen();
        if (input_result != 1){
            printf("Invalid place ID\n");
            continue;
        }
        if (input_place_id == 0)
            break;
        
        struct place place_target;
        place_target.place_id = input_place_id;
        struct place *search_place_result = place_list->place_tree->search(place_list->place_tree, &place_target);
        if (search_place_result == NULL){
            printf("Invalid place ID\n");
            continue;
        }

        place_record lower_bound_target;
        lower_bound_target.time = time_lower_bound;
        int lower_bound_index = lower_bound(search_place_result->path->array, &lower_bound_target, search_place_result->path->num_of_element, \
        search_place_result->path->element_size, time_compare_function);

        place_record upper_bound_target;
        upper_bound_target.time = time_upper_bound;
        int upper_bound_index = upper_bound(search_place_result->path->array, &upper_bound_target, search_place_result->path->num_of_element, \
        search_place_result->path->element_size, time_compare_function);

        if (lower_bound_index == -1 || upper_bound_index == -1){
            printf("no record\n");
            return;
        }

        if (lower_bound_index > upper_bound_index){
            set_and_print_error_message("lower bound greater than upper bound\n");
            return;
        }

        printf("Place ID : %d, record from %s to %s\n", input_place_id, time_lower_bound_string, time_upper_bound_string);
        printf("\n");
        for (int i = lower_bound_index; i <= upper_bound_index; i++){
            strftime(time_lower_bound_string, 40, "%Y-%m-%d %H:%M:%S", gmtime(&(((place_record *)search_place_result->path->array)[i].time)));
            printf("time : %s,\t\tstudent ID : %d\n", time_lower_bound_string, ((place_record *)search_place_result->path->array)[i].student_id);
        }
        printf("\n");
        printf("Press Enter to continue...\n");
        fflush_stdin();
        clear_screen();
        break;
    }
    
}