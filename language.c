#include "language.h"

// undone : search() hotspot()

int language;

char *welcome_message;
char *features_list;
char *option_err_msg;
char *seg_err_msg;
char *record_msg;
char *record_success;
char *delete_msg;
char *format_err_msg;
char *illegal_retrieval;
char *deletion_applied;
char *search_options;

char *search_student_id1;
char *search_student_id2;
char *search_student_id3;
char *invalid_id_err_msg;
char *no_record_err_msg ;
char *boundary_err_msg;
char *search_student_id4;
char *search_student_id5;
char *enter_continue;

char *student_id_msg;
char *place_id_msg;
char *time_msg;
char *visited_time_msg;

char welcome_message_en[] =
    "In this program, we will show the efficiency of avl tree compared with other data structure.\n"
    "Current version : Adelson-Velskii and Landis tree.\n"
    "Select options below to interact with database.\n"
    "Press Enter to continue\n";

char welcome_message_cn[] =
    "在這個程式中, 我們將展示avl tree相比其他資料結構所帶來的高效率。\n"
    "當前版本 : 阿傑爾松-韋利斯基與蘭迪斯樹\n"
    "接下來, 您可以透過以下選項來與資料庫互動。\n"
    "按下 Enter 鍵以繼續...\n";

char features_list_en[] =
    "-----------------------------\n"
    "[0] : End\n"
    "[1] : Search a student ID, the output will be students whose footprint overlaps \n"
    "[2] : Add new footprint to database.\n"
    "[3] : Delete a specific footprint.\n"
    "[4] : Campus hot spot analyze.\n"
    "[5] : User's preference Setting\n";

char features_list_cn[] =
    "-----------------------------\n"
    "[0] : 終止程式\n"
    "[1] : 搜尋一個學生學號, 程式將輸出足跡重疊者\n"
    "[2] : 在資料庫中添加一個新足跡\n"
    "[3] : 在資料庫中移出一個已存在的足跡\n"
    "[4] : 校園熱點-數據統計\n"
    "[5] : 使用者偏好設定\n";

char option_err_msg_en[] =
    "Invalid option detected! Please try again.\n";

char option_err_msg_cn[] =
    "偵測到無效選項! 請重新輸入。\n";

char seg_err_msg_en[] =
    "Segmentation fault detected!\n";

char seg_err_msg_cn[] =
    "偵測到記憶體區段錯誤!\n";

char record_en[] =
    "Please input student ID and place ID you want to record\n"
    "Input format : [student ID] [place ID]\n"
    "(Input 0 if you want to leave)\n"
    "Input : ";

char record_cn[] =
    "請輸入您想記錄的學生足跡\n"
    "輸入格式 : [學號] [場所代碼]\n"
    "(若您想跳出此功能，請輸入[0]。)\n"
    "您的輸入 : ";

char record_success_en[] =
    "Record success !\n";

char record_success_cn[] =
    "成功添加足跡!\n";

char delete_en[] =
    "Please input the data you want to delete\n"
    "Input format : [student ID] [place ID] [target time]\n"
    "time format : yyyy-mm-dd\n"
    "(input 0 if you want to leave)\n"
    "Input : \n";

char delete_cn[] = 
    "請輸入您想刪除的資料\n"
    "輸入格式 : [學號] [場所代碼] [目標時間]\n"
    "時間格式 : yyyy-mm-dd\n"
    "(若您想跳出此功能，請輸入[0]。)\n"
    "您的輸入 : ";

char format_err_msg_en[] =
    "Input format error detected!\n";

char format_err_msg_cn[] =
    "偵測到輸入格式錯誤!\n";

char illegal_retrieval_en[] =
    "Illegal data retrival detected!\n";

char illegal_retrieval_cn[] =
    "偵測到非法資料檢索!\n";

char deletion_applied_en[] =
    "Deletion applied !\n";

char deletion_applied_cn[] =
    "成功刪除足跡!\n";

char search_options_en[] =
    "[0] : Leave this function, and return to previous procedure.\n"
    "[1] : 「Overlapped Footprint, *Seer*」 : Search a 'target' student ID, the output will be "
    "people whose footprint overlapped that of 'target', within a specific time interval.\n"
    "[2] : 「Visitor's Footprint, *Bloodhound*」 : Search a 'target' place ID, the output will be "
    "people who visited this place, within a specific time interval.\n"
    "Note : Time interval can be altered based on your preference, please go to 'settings'"
    "for further information.\n";
char search_options_cn[] =
    "[0] : 離開此功能，並返回上一頁\n"
    "[1] : 「重疊足跡--席爾」 : 搜尋一個'目標學號', 輸出 "
    "所有在指定時段內, 和'目標'足跡重疊者。\n"
    "[2] : 「拜訪足跡--尋血犬」 : 搜尋一個'目標場所代碼', 輸出 "
    "所有在指定時段內，拜訪過'目標'場所的人。\n"
    "提示 : 時段是可以根據您的偏好更改的, 詳細請至'設定'。\n";

char search_student_id1_en[] = "search region : from ";
char search_student_id2_en[] = " to ";
char search_student_id3_en[] = "\n"
    "Note : This is a closed region (Head and tail are included)\n"
    "Input 0 if you want to leave\n"
    "Please input student ID : ";
char invalid_id_err_msg_en[] = "Invalid student ID\n";
char no_record_err_msg_en[] = "No record\n";
char boundary_err_msg_en[] = "Error : Lower bound greater than upper bound\n";
char search_student_id4_en[] = "Student ID : ";
char search_student_id5_en[] = "'s visit recorded.\n";
char enter_continue_en[] = "Press Enter to continue...\n";

char search_student_id1_cn[] = "搜尋區間 : 從 ";
char search_student_id2_cn[] = " 到 ";
char search_student_id3_cn[] = "\n"
    "提示 : 此區間為'閉'區間\n"
    "若您想離開, 請輸入[0]\n"
    "請輸入學號 : ";
char invalid_id_err_msg_cn[] = "無效的學號!\n";
char no_record_err_msg_cn[] = "沒有紀錄!\n";
char boundary_err_msg_cn[] = "錯誤 : 下界大於上界\n";
char search_student_id4_cn[] = "學號 : ";
char search_student_id5_cn[] = " 的拜訪紀錄。\n";
char enter_continue_cn[] = "按下Enter鍵以繼續...\n";

char student_id_msg_en[] = "student ID : ";
char student_id_msg_cn[] = "學號 : ";
char place_id_msg_en[] = "place ID : ";
char place_id_msg_cn[] = "場所代碼 : ";
char time_msg_en[] = "time : ";
char time_msg_cn[] = "時間 : ";
char visited_time_msg_en[] = "visited time : ";
char visited_time_msg_cn[] = "拜訪次數 : ";

void choose_language(){
    while (1){
        int input_option;
        printf("Please choose your language.\n");
        printf("選擇你的語言\n");
        printf("[1] English\n");
        printf("[2] 中文\n");
        int input_result = scanf("%2d", &input_option);
        clear_screen();
        fflush_stdin();
        if (input_result != 1){
            printf("%s", format_err_msg_en);
            printf("%s", format_err_msg_cn);
            continue;
        }

        if (input_option == ENGLISH){
            language = ENGLISH;
            break;
        }

        if (input_option == CHINESE){
            language = CHINESE;
            break;
        }

        printf("%s", format_err_msg_en);
        printf("%s", format_err_msg_cn);
    }
}

void decide_message(){
    if (language == ENGLISH){
        welcome_message = &welcome_message_en[0];
        features_list = &features_list_en[0];
        option_err_msg = &option_err_msg_en[0];
        seg_err_msg = &seg_err_msg_en[0];
        record_msg = &record_en[0];
        record_success = &record_success_en[0];
        delete_msg = &delete_en[0];
        format_err_msg = &format_err_msg_en[0];
        illegal_retrieval = &illegal_retrieval_en[0];
        deletion_applied = &deletion_applied_en[0];
        search_options = &search_options_en[0];

        search_student_id1 = &search_student_id1_en[0];
        search_student_id2 = &search_student_id2_en[0];
        search_student_id3 = &search_student_id3_en[0];
        invalid_id_err_msg = &invalid_id_err_msg_en[0];
        no_record_err_msg  = &no_record_err_msg_en[0];
        boundary_err_msg = &boundary_err_msg_en[0];
        search_student_id4 = &search_student_id4_en[0];
        search_student_id5 = &search_student_id5_en[0];
        enter_continue = &enter_continue_en[0];

        student_id_msg = &student_id_msg_en[0];
        place_id_msg = &place_id_msg_en[0];
        time_msg = &time_msg_en[0];
        visited_time_msg = &visited_time_msg_en[0];
        return;
    }

    if (language == CHINESE){
        welcome_message = &welcome_message_cn[0];
        features_list = &features_list_cn[0];
        option_err_msg = &option_err_msg_cn[0];
        seg_err_msg = &seg_err_msg_cn[0];
        record_msg = &record_cn[0];
        record_success = &record_success_cn[0];
        delete_msg = &delete_cn[0];
        format_err_msg = &format_err_msg_cn[0];
        illegal_retrieval = &illegal_retrieval_cn[0];
        deletion_applied = &deletion_applied_cn[0];
        search_options = &search_options_cn[0];

        search_student_id1 = &search_student_id1_cn[0];
        search_student_id2 = &search_student_id2_cn[0];
        search_student_id3 = &search_student_id3_cn[0];
        invalid_id_err_msg = &invalid_id_err_msg_cn[0];
        no_record_err_msg  = &no_record_err_msg_cn[0];
        boundary_err_msg = &boundary_err_msg_cn[0];
        search_student_id4 = &search_student_id4_cn[0];
        search_student_id5 = &search_student_id5_cn[0];
        enter_continue = &enter_continue_cn[0];

        student_id_msg = &student_id_msg_cn[0];
        place_id_msg = &place_id_msg_cn[0];
        time_msg = &time_msg_cn[0];
        visited_time_msg = &visited_time_msg_cn[0];
        return;
    }

    printf("language error\n");
    printf("語言錯誤\n");
}