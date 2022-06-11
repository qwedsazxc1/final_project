#include "setting.h"

static void change_hot_spot_standard();
static void change_setting_value(int *variable_be_changed, const char *variable_name, int upper_bound);
static void change_default_date();

int hot_spot_standard = 0;
struct tm default_date;
char default_date_string[50];

int read_from_setting(){
    errno = 0;
    FILE *setting = fopen("setting.txt", "r");
    if (setting == NULL){
        perror("fopen");
        return -1;
    }
    int read_result = fscanf(setting,   "hot spot standard : %9d\n"
                                        "default date : %40s"
                                       , &hot_spot_standard, default_date_string);
    if (read_result != 2){
        set_and_print_error_message("hot_spot_standard : read setting error\n");
        return -1;
    }

    if (strptime(default_date_string, "%Y-%m-%d", &default_date) == NULL){
        set_and_print_error_message("default_date : read error\n");
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
    fprintf(setting, "hot spot standard : %d\n", hot_spot_standard);
    fprintf(setting, "default date : %s\n", default_date_string);
}

void change_setting(){
    while (1){
        int option;
        printf("[0] : leave\n");
        printf("[1] : hot spot standard = %d\n", hot_spot_standard); 
        printf("[2] : default date = %s\n", default_date_string);
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

        if (option == 2){
            change_default_date();
            continue;
        }
        printf("invalid option\n");
    }
    
}

static void change_setting_value(int *variable_be_changed, const char *variable_name, int upper_bound){
    while (1){
        int value;
        printf("%s = %d\n", variable_name, *variable_be_changed);
        printf("input -1 if you don't want to change the value\n");
        printf("input the value you want change : ");
        int input_result = scanf("%9d", &value);
        fflush_stdin();
        clear_screen();
        if (input_result != 1){
            printf("Invalid option\n");
            continue;
        }
        if (value == -1)
            break;
        
        if (value < -1 || value > upper_bound){
            printf("Invalid option\n");
            continue;
        }
        *variable_be_changed = value;
        break;
    }
}

static void change_hot_spot_standard(){
    change_setting_value(&hot_spot_standard, "hot spot standard", 1e8);
}

static void change_default_date(){
    while (1){
        char input_time_string[50];
        printf("default_date = %s\n", default_date_string);
        printf("Input format : yyyy-mm-dd\n");
        printf("input 0 if you don't want to change the value\n");
        int input_result = scanf("%40s", input_time_string);
        fflush_stdin();
        clear_screen();
        if (input_result != 1){
            printf("invalid option\n");
            continue;
        }
        int leave_option = -1;
        if ((input_result = sscanf(input_time_string, "%5d", &leave_option)) != 1){
            printf("invalid option\n");
            continue;
        }
        if (leave_option == 0)
            break;
        
        if (strptime(input_time_string, "%Y-%m-%d", &default_date) == NULL){
            printf("invalid option\n");
            continue;
        }

        strcpy(default_date_string, input_time_string);
        break;
    }
    
}