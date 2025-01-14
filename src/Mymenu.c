#include "mymenu.h"
#include "users.h"


void draw_logo(int y, char *message, int color_pair) {
    int currenty = y;
    int startx = (COLS - 40) / 2;

    mvprintw(currenty++, startx, "  _____   ____   _____ _    _ ______ ");
    mvprintw(currenty++, startx, " |  __ \\ / __ \\ / ____| |  | |  ____|");
    mvprintw(currenty++, startx, " | |__) | |  | | |  __| |  | | |__    ");
    mvprintw(currenty++, startx, " |  _  /| |  | | | |_ | |  | |  __|  ");
    mvprintw(currenty++, startx, " | | \\ \\| |__| | |__| | |__| | |____ ");
    mvprintw(currenty++, startx, " |_|  \\_\\\\____/ \\_____|\\____/|______|");
    mvprintw(currenty++, startx, "                                     \n");
    attron(COLOR_PAIR(color_pair));
    mvprintw(currenty + 2, startx + (40 - strlen(message)) / 2, "%s", message);
    attroff(COLOR_PAIR(color_pair));

}


int menu(char* message, int color, const char **options, int size) {
    const char* pass = "*AliAlmasi";    
    start_color();
    WINDOW *menu_win;
    int ch, win_height, win_width;
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
        draw_logo(1, message, color);
        attroff(COLOR_PAIR(1));
        box(stdscr, 0, 0);
        mvprintw(LINES - 2, 0, "use arrow keys to navigate and press Enter to select!");
        box(menu_win, 0, 0);
        int rows, cols;
        getmaxyx(menu_win, rows, cols);
        for(int i = 0; i < size; i++) {
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
            choice = (choice == size - 1) ? choice : (choice + 1);
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
            if(passchecker == 9) {
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
        if(LINES > 6 && COLS > 104) {
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

int sign_up_menu(Users **arr, int *n) {
    char username[MAX_LEN] = {};
    char email[MAX_LEN] = {};
    char pass[MAX_LEN] = {};
    curs_set(true);
    while(true) {
        draw_logo(1 , "Credit: Ali Almasi", 3);
        echo();
        attron(COLOR_PAIR(4));
        mvprintw((LINES - 7) / 2 + 7, (COLS - 11) / 2, "%s", "Username: ");
        
        getnstr(username, MAX_LEN);
        noecho();
        attroff(COLOR_PAIR(4));
        refresh();
        clear();
        if(check_username(arr, *n, username) != NULL) {
            attron(COLOR_PAIR(3));
            mvprintw((LINES - 7) / 2 + 5, (COLS - 34) / 2, "This Username is already exist!");
            attroff(COLOR_PAIR(3));
            continue;
        }
        break;
    }
    while (true) {
        echo();
        attron(COLOR_PAIR(4));        
        mvprintw((LINES - 7) / 2 + 7, (COLS - 8)/ 2, "%s", "Email: ");
        getnstr(email, MAX_LEN);
        noecho();
        attroff(COLOR_PAIR(4));
        refresh();
        clear();
        if(check_email(email) == 0) {
            attron(COLOR_PAIR(3));
            mvprintw((LINES - 7) / 2 + 5, (COLS - 34) / 2, "Your email is invalid! try again ");
            attroff(COLOR_PAIR(3));
            continue;
        }
        break;
    }
    while (true) {
        attron(COLOR_PAIR(4));
        mvprintw((LINES - 7) / 2 + 7, (COLS - 60) / 2 , "%s", "Password: (type ':rand' to generate random password)");
        getnstr(pass, MAX_LEN);
        attroff(COLOR_PAIR(4));
        refresh();
        clear();
        if(!strcmp(pass, ":rand")) {
            mvprintw((LINES - 7) / 2 + 5, (COLS - 45) / 2, "your generated password is : '%s'", "test");
            
        }
        int test = pass_check(pass);
        if(((test >> 3) & 1 )!= 1) {
            attron(COLOR_PAIR(3));
            mvprintw((LINES - 7) / 2 + 5, (COLS - 45) / 2, "Your password must be at least 7 characters.");
            attroff(COLOR_PAIR(3));
            continue;
        }
        if(((test >> 2) & 1 )!= 1) {
            attron(COLOR_PAIR(3));
            mvprintw((LINES - 7) / 2 + 5, (COLS - 35) / 2, "Your password must contain number.");
            attroff(COLOR_PAIR(3));
            continue;
        }
        if(((test >> 1) & 1 )!= 1) {
            attron(COLOR_PAIR(3));
            mvprintw((LINES - 7) / 2 + 5, (COLS - 41) / 2, "Your password must contain upper letter.");
            attroff(COLOR_PAIR(3));
            continue;
        }

        if((test & 1 )!= 1) {
            attron(COLOR_PAIR(3));
            mvprintw((LINES - 7) / 2 + 5, (COLS - 41) / 2, "Your password must contain lower letter.");
            attroff(COLOR_PAIR(3));
            continue;
        }
        break;
    }
    curs_set(false);
    sign_up(arr, n, username, pass, email);
    return 0;
}

int login_menu(Users **arr, int n) {
    char username[MAX_LEN], password[MAX_LEN];
    draw_logo(1, "Login User :", 5);
    attron(COLOR_PAIR(4));
    mvprintw((LINES - 10) / 2 + 1, (COLS - 12) / 2, "Username : ");
    mvprintw((LINES - 10) / 2 + 3, (COLS - 12) / 2, "Password : ");
    attroff(COLOR_PAIR(4));
    Users *temp = NULL;
    while(1) {
        attron(COLOR_PAIR(4));
        mvprintw((LINES - 10) / 2 + 1, (COLS - 12) / 2, "Username : ");
        mvprintw((LINES - 10) / 2 + 3, (COLS - 12) / 2, "Password : ");
        move((LINES - 10) / 2 + 1, (COLS - 12) / 2 + 11);
        attroff(COLOR_PAIR(4));
        if(temp != NULL) {
            draw_logo(1, "Enter Password for user", 2);
            break;
        }
        echo();
        getnstr(username, MAX_LEN);
        noecho();
        temp = check_username(arr, n, username);
        if(temp == NULL) {
            clear();
            draw_logo(1, "User didn't find!", 3);
            refresh();
            continue;
        }
    }
    while (1) {
        echo();
        attron(COLOR_PAIR(4));
        mvprintw((LINES - 10) / 2 + 1, (COLS - 12) / 2, "Username : ");
        mvprintw((LINES - 10) / 2 + 3, (COLS - 12) / 2, "Password : ");
        attroff(COLOR_PAIR(4));
        mvprintw((LINES - 10) / 2 + 1, (COLS - 12) / 2 + 11, "%s", username);
        move((LINES - 10) / 2 + 3, (COLS - 12) / 2 + 11);
        getnstr(password, MAX_LEN);
        noecho();
        clear();
        if(!log_in(arr, n, username, password)) {
            draw_logo(1, "Wrong password", 3);
            continue;
        }
        return 1;
    }
}

int pregame_menu() {

}