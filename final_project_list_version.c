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
#define RECORD 2
#define LEAVE 0
#define DELETE 3
#define HOT_SPOTS 4
#define SEARCH 1
#define SETTING 5

struct hot_spot{
    int place_id;
    unsigned long long number_of_people;
};
vector hot_spot_list = NULL;

char file_name[85];

void print_usage();
void seg_fault(int singo);
void clear_hot_spot(void);
void initial(int argc, char *argv[]);

int main(int argc, char *argv[]){
    initial(argc, argv);
    clear_screen();
    printf("In this program, we will show the efficiency of avl tree compared with other data structures.\n");
    printf("Current version : linked list(double direction).\n");
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
            search();
            continue;
        }

        if (options == RECORD){
            record();
            continue;
        }

        // delete footprints
        if (options == DELETE){
            delete();
            continue;
        }

        if (options == HOT_SPOTS){
            hot_spots();
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
    
    

}

void seg_fault(int singo){
    fprintf(stderr, "Segmentation fault\n");
}

void clear_hot_spot(void){
    if (hot_spot_list != NULL){
        destory_vector(&hot_spot_list);
    }
}

void deal_with_argv(int argc, char *argv[]){
    if (argc < 1 && argc > 3){
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
        if (strcmp("-h", *option) == 0 || strcmp("--help", *option) == 0){
            print_usage();
            exit(0);
        }
        printf("unknown option : %s\n", *option);
        print_usage();
        exit(0);
    }
}

void print_usage(){
    printf("Usage : ./avl_tree_ver [option]\n");
    printf("option :\n");
    printf("-f, --file <csv file>\t, load informtaion from csv file, default is footprint.csv\n");
}