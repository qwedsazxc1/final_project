#include "setting.h"

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