#include "../include/mymenu.h"
#include "../include/users.h"
Users *active_user;
Users *arr;
int users_count = 0;
int main() {
    Users temp_user;
    temp_user.start_time = time(NULL);
    strcpy(temp_user.username, "Guest User");
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

    init_color(10, 700, 700, 700); //silver
    init_color(11, 800, 500, 200); //bronze
    init_color(12, 1000, 843, 0); //gold
    init_pair(10, 10, COLOR_BLACK);
    init_pair(11, 11, COLOR_BLACK);
    init_pair(12, 12, COLOR_BLACK);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);
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
            val = pregame_menu();
            if(val == 27) {
                active_user = NULL;
                choose = menu("Game menu :", 2, options, 4);
            }
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
            active_user = &temp_user;
            active_user->active_floor = 0;
            active_user->difficulty = 1;
            active_user->player_color = 1;
            int val = pregame_menu();
            if(val == 27) {
                active_user = NULL;
                choose = menu("Game menu :", 2, options, 4);
            }
        }
        else if(choose == 27) {
            break;
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
            printf("Somthing went wrong! Error : %d", choose);
            return choose;

        }
    }
    endwin();
    refresh();
    return 0;
}