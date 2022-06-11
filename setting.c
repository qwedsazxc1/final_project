#include "setting.h"

static void change_hot_spot_standard();
static void change_setting_value(int *variable_be_changed, const char *variable_name, int upper_bound);
static void change_default_date();
static void change_search_front_date();
static void change_search_after_date();
static void change_search_front_minute();
static void change_search_after_minute();

int search_front_minute;
int search_after_minute;
int search_front_date;
int search_after_date;
int hot_spot_standard;
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
                                        "default date : %40s\n"
                                        "search front date : %9d\n"
                                        "search after date : %9d\n"
                                        "search front minute : %9d\n"
                                        "search after minute : %9d"
                                       , &hot_spot_standard, default_date_string, &search_front_date, &search_after_date, &search_front_minute, &search_after_minute);
    if (read_result != 6){
        set_and_print_error_message("hot_spot_standard : read setting error\n");
        return -1;
    }

    memset(&default_date, 0, sizeof(struct tm));
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
    fprintf(setting, "search front date : %d\n", search_front_date);
    fprintf(setting, "search after date : %d\n", search_after_date);
    fprintf(setting, "search front minute : %d\n", search_front_minute);
    fprintf(setting, "search after minute : %d\n", search_after_minute);
}

void change_setting(){
    while (1){
        int option;
        printf("[0] : leave\n");
        printf("[1] : hot spot standard = %d\n", hot_spot_standard); 
        printf("[2] : default date = %s\n", default_date_string);
        printf("[3] : search front date(unit : day) = %d\n", search_front_date);
        printf("[4] : search after date(unit : day) = %d\n", search_after_date);
        printf("[5] : search front minute(unit : minute) = %d\n", search_front_minute);
        printf("[6] : search after minute(unit : minute) = %d\n", search_after_minute);
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

        if (option == 3){
            change_search_front_date();
            continue;
        }

        if (option == 4){
            change_search_after_date();
            continue;
        }

        if (option == 5){
            change_search_front_minute();
            continue;
        }

        if (option == 6){
            change_search_after_minute();
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

static void change_search_front_date(){
    change_setting_value(&search_front_date, "search front date(unit : day)", 1e9);
}

static void change_search_after_date(){
    change_setting_value(&search_after_date, "search after date(unit : day)", 1e9);
}

static void change_search_front_minute(){
    change_setting_value(&search_front_minute, "search front minute(unit : minute)", 1e9);
}

static void change_search_after_minute(){
    change_setting_value(&search_after_minute, "search after minute(unit : minute)", 1e9);
}

unsigned long long get_time_lower_bound(){
    unsigned long long time_lower_bound = timegm(&default_date);
    time_lower_bound -= SECOND_IN_A_DAY * search_front_date;
    return time_lower_bound;
}

unsigned long long get_time_upper_bound(){
    unsigned long long time_upper_bound = timegm(&default_date);
    time_upper_bound += SECOND_IN_A_DAY * (search_after_date + 1);
    return time_upper_bound - 1;
}

time_t get_search_visited_time_lower_bound(time_t time){
    time -= SECOND_IN_A_MINUTE * search_front_minute;
    return time;
}

time_t get_search_visited_time_upper_bound(time_t time){
    time += SECOND_IN_A_MINUTE * search_after_minute;
    return time;
}