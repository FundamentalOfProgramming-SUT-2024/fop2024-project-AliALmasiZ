#include "funcs.h"
#include <ncurses.h>

int main() {
    initscr();
    
    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support colors.\n");
        return 1;
    }
    start_color();
    
    
    getch();
    endwin();
}