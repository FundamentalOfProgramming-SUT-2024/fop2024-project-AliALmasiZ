#include "funcs.h"
#include "menu.h"
#include <ncurses.h>
#include <stdlib.h>

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
    // draw_logo(1);
    
    int choose = draw_menu();
    attron(COLOR_PAIR(1));
    printw("your choose is : %d", choose);
    attroff(COLOR_PAIR(1));
    getch();
    endwin();
}