#include "mymenu.h"
#include "users.h"
Users *active_user;

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
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    //----------------------------------------------
    const char *options[] = {"    Log in    ", "   Sign up    ", "Play as Guest ", "  Exit Game   "};
    int choose = menu("Credit: Ali Almasi", 3, options, 4);
    while(1) {
        if (choose == 3) {

            goodbye_logo();
            return 0;
        }
        else if (choose == 0) { //login
            login_menu(&arr, users_count);
            break;
        }
        else if(choose == 1) { //sign in
            sign_up_menu(&arr, &users_count);
            choose = menu("User registered successfully", 2, options, 4);

        }
        else if(choose == 2) { //guest
            choose = menu("Credit: Ali Almasi", 3, options, 4);
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
    endwin();
    refresh();
    return 0;

}