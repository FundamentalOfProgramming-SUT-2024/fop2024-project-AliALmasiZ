#include "mymenu.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>

int main() {
    // initial commands :
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    cbreak();
    keypad(stdscr, true);
    noecho();
    // color pairs :                    
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    int choose = init_menu();
    if (choose == 3) {
        goodbye_logo();
        return 0;
    }
    refresh();
    endwin();

}