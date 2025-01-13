#include "mymenu.h"
#include "users.h"



int main() {
    Users *arr = calloc(MAX_USERS, sizeof(Users));
    int users_count = 0;
    users_count = load_users(&arr);
    //--------------initial commands----------------
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    cbreak();
    keypad(stdscr, true);
    noecho();
    curs_set(FALSE);
    //-----------color pairs------------------------                    
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    //----------------------------------------------
    int choose = init_menu("Credit: Ali Almasi", 3);
    while(1) {
        if (choose == 3) {

            goodbye_logo();
            return 0;
        }
        else if (choose == 0) { //login
            choose = init_menu("Credit: Ali Almasi", 3);
        }
        else if(choose == 1) { //sign in
            sign_in_menu(&arr, &users_count);
            choose = init_menu("User signed in successfully", 2);

        }
        else if(choose == 2) { //guest
            choose = init_menu("Credit: Ali Almasi", 3);
        }
        else if (choose == -1) {
            endwin();
            for(int i = 0; i < users_count; i++) {
                printf("%s\n", arr[i].username);
            }
            printf("%d\n", users_count);
            return 0;
        }
        else {
            clear();
            refresh();
            endwin();
            printf("Somthing went wrong\nError code : %d", choose);
            return 0;
        }
    }
    refresh();
    endwin();

}