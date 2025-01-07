#include "menu.h"
#include <menu.h>
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

int draw_menu() {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    ITEM *items[5];
    MENU *menu;
    WINDOW *menu_win;
    int ch, win_height, win_width;
    // attron(COLOR_PAIR(1));
    draw_logo(1);

    items[0] = new_item("Log in", "s");
    items[1] = new_item("Sign in", "s");
    items[2] = new_item("Play as Guest", "s");
    items[3] = new_item("Exit Game", "s");
    items[4] = NULL;

    menu = new_menu(items);
    

    win_height = 20;
    win_width = 50;
    int start_y = (LINES) / 2;
    int start_x = (COLS) / 2;

    menu_win = newwin(win_height, win_width, start_y, start_x);
    
    keypad(menu_win, true);

    set_menu_win(menu, menu_win);
    set_menu_sub(menu, derwin(menu_win, win_height - 2, win_width - 4, 1, 2));
    
    set_menu_mark(menu, "→");
    
    werase(menu_win);
    box(menu_win, 0, 0);
    // box(menu_win, ACS_VLINE, ACS_HLINE);
    wrefresh(menu_win);

    post_menu(menu);
    refresh();
    wrefresh(menu_win);
    // attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(1));
    mvprintw(LINES - 2, 0, "use arrow keys to navigate and press Enter to select!");
    attroff(COLOR_PAIR(1));

    refresh();
    while((ch = wgetch(menu_win)) != '\n') {
        if(ch == KEY_DOWN) {
            menu_driver(menu, REQ_DOWN_ITEM);
        }
        else if(ch == KEY_UP) {
            menu_driver(menu, REQ_UP_ITEM);
        }
        wrefresh(menu_win);
    }
    int res = item_index(current_item(menu));
    unpost_menu(menu);
    free_menu(menu);
    for(int i = 0; i < 5; i++) {
        free_item(items[i]);
    }
    delwin(menu_win);
    refresh();
    return res;
}




