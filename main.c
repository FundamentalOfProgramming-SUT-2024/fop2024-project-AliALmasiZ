#include "mymenu.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // initial commands :
    initscr();
    start_color();
    cbreak();
    keypad(stdscr, true);
    noecho();
    // color pairs :                    
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    int choose = init_menu();
    
    refresh();

}