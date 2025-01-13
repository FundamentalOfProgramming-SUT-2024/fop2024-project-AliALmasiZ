#include "menu.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>

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
    const char* pass = "AliAlmasi";    
    start_color();
    WINDOW *menu_win;
    int ch, win_height, win_width;
    const char *options[] = {"    Log in    ", "   Sign in    ", "Play as Guest ", "  Exit Game   "};
    int choice = 0;
    win_height = 10;
    win_width = 40;
    int start_y = (LINES - win_height - 7) / 2 + 7;
    int start_x = (COLS - win_width) / 2 ;
    menu_win = newwin(win_height, win_width, start_y, start_x);
    keypad(menu_win, true);

    attron(COLOR_PAIR(1));
    attroff(COLOR_PAIR(1));
    refresh();
    wattron(menu_win, COLOR_PAIR(1));
    int passchecker = 0;
    while(true) {
        clear();
        if(LINES < 20 || COLS < 42) {
            delwin(menu_win);
            return 400;
        }
        start_y = (LINES - win_height - 7) / 2 + 7;
        start_x = (COLS - win_width) / 2 ;
        mvwin(menu_win, start_y, start_x);
        wclear(menu_win);
        attron(COLOR_PAIR(1));
        draw_logo(1);
        attroff(COLOR_PAIR(1));
        box(stdscr, 0, 0);
        mvprintw(LINES - 2, 0, "use arrow keys to navigate and press Enter to select!");
        box(menu_win, 0, 0);
        int rows, cols;
        getmaxyx(menu_win, rows, cols);
        for(int i = 0; i < 4; i++) {
            if(choice == i)
                wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, (rows - 4) / 2 + i, (cols - 15) / 2, "%s", options[i]);
            if(choice == i)
                wattroff(menu_win, A_REVERSE);
        }
        refresh();
        wrefresh(menu_win);
        int c = getch();
        
        if(c == KEY_DOWN) {
            choice = (choice == 3) ? choice : (choice + 1);
        }
        else if(c == KEY_UP) {
            choice = (choice == 0) ? choice : (choice - 1);
        }
        else if(c == '\n') {
            wattroff(menu_win, COLOR_PAIR(1));
            wclear(menu_win);
            clear();
            delwin(menu_win);
            return choice;
        }
        else if(c == pass[passchecker]){
            if(passchecker == 8) {
                wattroff(menu_win, COLOR_PAIR(1));
                wclear(menu_win);
                clear();
                delwin(menu_win);
                return -1;
            }
            passchecker++;
            continue;
        }
        passchecker = 0;
        // refresh();
    }
}

void goodbye_logo() {
    clear();
    wchar_t *line[] = {
        L" ░▒▓██████▓▒░   ░▒▓██████▓▒░   ░▒▓██████▓▒░  ░▒▓███████▓▒░  ░▒▓███████▓▒░  ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓████████▓▒░ ",
        L"░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░        ",
        L"░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░        ",
        L"░▒▓█▓▒▒▓███▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓███████▓▒░   ░▒▓██████▓▒░  ░▒▓██████▓▒░   ",
        L"░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░    ░▒▓█▓▒░     ░▒▓█▓▒░        ",
        L"░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░    ░▒▓█▓▒░     ░▒▓█▓▒░        ",
        L" ░▒▓██████▓▒░   ░▒▓██████▓▒░   ░▒▓██████▓▒░  ░▒▓███████▓▒░  ░▒▓███████▓▒░     ░▒▓█▓▒░     ░▒▓████████▓▒░ ",
    };
        attron(COLOR_PAIR(2));
        if(LINES > 6 && COLS > 106) {
            for(int i = 0; i < 7; i++) {
                mvprintw(LINES / 2 - 3 + i, (COLS - 106) / 2,"%ls", line[i]);
            }
        }
        else {
            mvprintw(LINES / 2, (COLS - 8) / 2,"GOODBYE");

        }
        refresh();
        attroff(COLOR_PAIR(2));
        sleep(2);
        endwin();
}

int sign_in_menu() {

}