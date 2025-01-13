#include "mymenu.h"
#include "users.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>  


int main() {
    Users arr[MAX_USERS] = {0};
    int users_count = 0;
    
    // initial commands :
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    cbreak();
    keypad(stdscr, true);
    noecho();
    curs_set(FALSE);
    // color pairs :                    
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    int choose = init_menu();
    if (choose == 3) {

        goodbye_logo();
        return 0;
    }
    else if (choose == 0) { //login
        
    }
    else if(choose == 1) { //sign in

    }
    else if(choose == 2) { //guest

    }
    else {
        clear();
        endwin();
        printf("Somthing went wrong\nError code : %d", choose);
        return 0;
    }
    refresh();
    endwin();

}