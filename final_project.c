/*
    This is Chung-Cheng University Computer science and Information engineering course : program design(II)'s final project
    Group : 電神阿宏與他的小夥伴
    participant :
    student ID : 410410021, name : Yi-Hong Lin, mail : linyihong1234@gmail.com
    student ID : 410410083
    student ID : 410410011, name : Chao-Ting Wu, mail : justinwu105@gamil.com
    student ID : 410410067
    student ID : 410410080
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

void print_out_check();
void initial(int argc, char *argv[]);
void deal_with_argv(int argc, char *argv[]);
void delete_path(int student_id, int place_id, unsigned long long at_time);
void clear_hot_spot();
int hot_spot_compare_function(const void *front, const void *back);
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

int main(int argc, char *argv[]){
    initial(argc, argv);
    //////////////////////////////////////////

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
        printf("[1] : 「重疊捕獲者」 : 查確診者、日期，跑出(誰)在(該日甚麼時間)在(哪裡)足跡重疊。\n");
        printf("[2] : 「健康檢測」 : 查任意學號，跑出是否曾有與確診者重疊的紀錄\n");
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

            //Input format : 確診者學號\n欲查詢日期(space)\n
            printf("請輸入欲查詢之「確診者學號」 :\n");
            //scanf
            printf("請輸入「指定日期」 :\n");
            //scanf
            // eg.410410083\n20220610\n
            printf("輸出：(學號)'s footprint overlapped, at (地點), (時間)\n");
            // eg.410410021's footprint overlapped, at 五嬤嬤, PM_4:00
            //    410410011's footprint overlapped, at 活動中心, AM_3:00
            // 若沒有查到任何重疊，則輸出以下
            printf("Confirmed Case (學號) didn't have footprints overlapped with anyone.\n");
            continue;
        }
        if (option == 2){
            // "Input format : 目標學號\n"
            printf("請輸入欲查詢之「目標學號」 :\n");
            //scanf
            // eg.410410083
            printf("輸出 : footprint overlapped with infected (學號), at (地點), (時間)\n");
            // eg.footprint overlapped with infected 410410083, at 五嬤嬤, PM4:00
            // 若沒有查到任何重疊，則輸出以下
            printf("輸出 : Congrats! Your footprints didn't overlap with any infected people in school.\n");
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
        printf("deletion appiled !\n");
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

void print_usage(){
    printf("Usage : ./avl_tree_ver [option]\n");
    printf("option :\n");
    printf("-f, --file <csv file>\t, load informtaion from csv file \n");
    printf("-ps, --printstu\tprint output sort by student id\n");
    printf("-pp, --printpla\tprint output sort by place id\n");
    return;
}