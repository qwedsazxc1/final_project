#include "setting.h"

static void change_hot_spot_standard();
static void change_setting_value(int *variable_be_changed, const char *variable_name, int upper_bound);
static void change_default_year();
static void change_default_month();
static void change_default_day();
static void change_default_hour();
static void change_default_minute();
static void change_default_second();


int hot_spot_standard = 0;
int default_year = 0;
int default_month = 0;
int default_day = 0;
int default_hour = 0;
int default_minute = 0;
int default_second = 0;

int read_from_setting(){
    errno = 0;
    FILE *setting = fopen("setting.txt", "r");
    if (setting == NULL){
        perror("fopen");
        return -1;
    }
    int read_result = fscanf(setting,   "hot spot standard : %9d\n" \
                                        "default year : %5d\n" \
                                        "default month : %3d\n" \
                                        "default day : %3d\n" \
                                        "default hour : %3d\n"
                                        "default minute : %3d\n"
                                        "default second : %3d"
                                       , &hot_spot_standard, &default_year, &default_month, &default_day, &default_hour, &default_minute, &default_second);
    if (read_result != 7){
        set_and_print_error_message("hot_spot_standard : read setting error\n");
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
    fprintf(setting, "default year : %d\n", default_year);
    fprintf(setting, "default month : %d\n", default_month);
    fprintf(setting, "default day : %d\n", default_day);
    fprintf(setting, "default hour : %d\n", default_hour);
    fprintf(setting, "default minute : %d\n", default_minute);
    fprintf(setting, "default second : %d\n", default_second);
}

void change_setting(){
    while (1){
        int option;
        printf("[0] : leave\n");
        printf("[1] hot spot standard = %d\n", hot_spot_standard);
        printf("[2] default year = %d\n", default_year);
        printf("[3] default month = %d\n", default_month);
        printf("[4] default day = %d\n", default_day);
        printf("[5] default hour = %d\n", default_hour);
        printf("[6] default minute = %d\n", default_minute);
        printf("[7] default second = %d\n", default_second);
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
            change_default_year();
            continue;
        }

        if (option == 3){
            change_default_month();
            continue;
        }

        if (option == 4){
            change_default_day();
            continue;
        }

        if (option == 5){
            change_default_hour();
            continue;
        }

        if (option == 6){
            change_default_minute();
            continue;
        }

        if (option == 7){
            change_default_second();
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

static void change_default_year(){
    change_setting_value(&default_year, "default year", 2038);
}

void print_input_time_format(){
    printf("time format : ");
    if (default_year == 0)
        printf("yyyy ");
    else
        printf("%d ", default_year);
    
    if (default_month == 0)
        printf("mm/");
    else
        printf("%d/", default_month);
    
    if (default_day == 0)
        printf("dd ");
    else
        printf("%d ", default_day);

    if (default_hour == 0)
        printf("hh:");
    else
        printf("%.2d:", default_hour);
    
    if (default_minute == 0)
        printf("mm:");
    else
        printf("%.2d:", default_minute);
    
    if (default_second == 0)
        printf("ss");
    else    
        printf("%.2d", default_second);
    
    printf("\n");
}

static void change_default_month(){
    change_setting_value(&default_month, "default month", 12);
}

static void change_default_day(){
    change_setting_value(&default_day, "default day", 31);
}

static void change_default_hour(){
    change_setting_value(&default_hour, "default hour", 23);
}

static void change_default_minute(){
    change_setting_value(&default_minute, "default minute", 59);
}

static void change_default_second(){
    change_setting_value(&default_second, "default second", 59);
}