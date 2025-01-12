#include "mymenu.h"
#include <ncurses.h>
#include <stdio.h>

void draw_logo(int y) {
    int currenty = y;
    int startx = (COLS - 40) / 2;

    mvprintw(currenty++, startx, "  _____   ____   _____ _    _ ______ ");
    mvprintw(currenty++, startx, " |  __ \\ / __ \\ / ____| |  | |  ____|");
    mvprintw(currenty++, startx, " | |__) | |  | | |  __| |  | | |__    ");
    mvprintw(currenty++, startx, " |  _  /| |  | | | |_ | |  | |  __|  ");
    mvprintw(currenty++, startx, " | | \\ \\| |__| | |__| | |__| | |____ ");
    mvprintw(currenty++, startx, " |_|  \\_\\\\____/ \\_____|\\____/|______|");
    mvprintw(currenty++, startx, "                                     ");
}


int init_menu() {
    start_color();
    WINDOW *menu_win;
    int ch, win_height, win_width;
    attron(COLOR_PAIR(1));
    draw_logo(1);
    attroff(COLOR_PAIR(1));
    const char *options[] = {"Log in", "Sign in", "Play as Guest", "Exit Game"};
    int choice = 0;
    win_height = 10;
    win_width = 40;
    int start_y = (LINES) / 2;
    int start_x = (COLS) / 2;
    menu_win = newwin(win_height, win_width, start_y, start_x);
    keypad(menu_win, true);

    attron(COLOR_PAIR(1));
    mvprintw(LINES - 2, 0, "use arrow keys to navigate and press Enter to select!");
    attroff(COLOR_PAIR(1));
    refresh();
    wattron(menu_win, COLOR_PAIR(1));
    while(true) {
        // clear();
        // wclear(menu_win);
        box(menu_win, 0, 0);
        int rows, cols;
        getmaxyx(menu_win, rows, cols);
        for(int i = 0; i < 4; i++) {
            if(choice == i)
                wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, (rows - 4) / 2 + i, cols / 2 - 5, "%s", options[i]);
            if(choice == i)
                wattroff(menu_win, A_REVERSE);
        }
        wrefresh(menu_win);
        int c = getch();
        switch (c) {
        case KEY_DOWN:
            choice = (choice == 3) ? choice : (choice + 1);
            break;
        case KEY_UP:
            choice = (choice == 0) ? choice : (choice - 1);
            break;
        case '\n':
            
            wattroff(menu_win, COLOR_PAIR(1));
            return choice;
        }

        // refresh();
    }
}
