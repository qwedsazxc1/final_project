#include "setting.h"

static void change_hot_spot_standard();

unsigned long long hot_spot_standard = 0;

int read_from_setting(){
    errno = 0;
    FILE *setting = fopen("setting.txt", "r");
    if (setting == NULL){
        perror("fopen");
        return -1;
    }
    if (fscanf(setting, "hot spot standard : %llu", &hot_spot_standard) != 1){
        set_and_print_error_message("hot_spot_standard : read setting error");
        return -1;
    }
    return 0;
}

void write_to_setting(){
    errno = 0;
    FILE *setting = fopen("setting.txt", "w");
    if (setting == NULL){
        perror("fopen");
        return;
    }
    fprintf(setting, "hot spot standard : %llu\n", hot_spot_standard);
}

void change_setting(){
    while (1){
        int option;
        printf("[0] : leave\n");
        printf("[1] hot spot standard = %llu\n", hot_spot_standard);
        printf("input the option that you want to change\n");

        int input_result = scanf("%2d", &option);
        fflush_stdin();
        clear_screen();
        if (input_result != 1){
            printf("invalid option\n");
            continue;
        }
        if (option == 0)
            break;
        
        if (option == 1){
            change_hot_spot_standard();
            continue;
        }

        printf("invalid option\n");
    }
    
}

static void change_hot_spot_standard(){
    while (1){
        unsigned long long value;
        printf("hot spot standard = %llu\n", hot_spot_standard);
        printf("input 0 if you don't want to change the value\n");
        printf("input the value you want change : ");
        int input_result = scanf("%30llu", &value);
        fflush_stdin();
        clear_screen();
        if (input_result != 1){
            printf("Invalid option\n");
            continue;
        }
        if (value == 0){
            break;
        }
        hot_spot_standard = value;
        break;
    }
}