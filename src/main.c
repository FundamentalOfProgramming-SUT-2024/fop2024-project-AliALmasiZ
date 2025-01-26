#include "../include/mymenu.h"
#include "../include/users.h"
Users *active_user;
Users *arr;
int users_count = 0;
int main() {
    srand(time(NULL));
    arr = calloc(MAX_USERS, sizeof(Users));
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
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    //----------------------------------------------
    const char *options[] = {"    Log in    ", "   Sign up    ", "Play as Guest ", "  Exit Game   "};
    int choose = menu("Credit: Ali Almasi", 3, options, 4);
    while(1) {
        if (choose == 3) {

            goodbye_logo();
            return 0;
        }
        else if (choose == 0) { //login
            int val = login_menu(&arr, users_count);
            if(val == 27) {
                choose = menu("Game menu :", 2, options, 4);
                continue;
            }
            pregame_menu();
            break;
        }
        else if(choose == 1) { //sign in
            char *s = "User registered successfully";
            int val = sign_up_menu(&arr, &users_count);
            if(val == 27) {
                s = "Game menu :";
            }
            choose = menu(s, 2, options, 4);
        }
        else if(choose == 2) { //guest
            pregame_menu();
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
            printf("Somthing went wrong");
            return choose;

        }
    }
    endwin();
    refresh();
    return 0;
}