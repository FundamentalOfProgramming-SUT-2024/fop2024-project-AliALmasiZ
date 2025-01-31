#include "../include/mymenu.h"
#include "../include/users.h"
#include "../include/games.h"


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
    attron(COLOR_PAIR(color_pair) | A_BOLD);
    mvprintw(currenty + 2, startx + (40 - strlen(message)) / 2, "%s", message);
    attroff(COLOR_PAIR(color_pair) | A_BOLD);
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
    box(stdscr, 0, 0);
    mvprintw(LINES - 3, 0, "Use arrow keys to navigate and press Enter to select!");
    mvprintw(LINES - 2, 0, "Press Esc key to go to main menu");

    while(true) {
        draw_logo(1 , "Credit: Ali Almasi", 3);
        echo();
        attron(COLOR_PAIR(4));
        mvprintw((LINES - 7) / 2 + 7, (COLS - 30) / 2, "%s", "Username: ");
        
        // getnstr(username, MAX_LEN);
        int val = getstring(stdscr, username, MAX_LEN, 1);
        if (val == 27) {
            clear();
            refresh();
            return 27;
        }
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
        mvprintw((LINES - 7) / 2 + 7, (COLS - 30)/ 2, "%s", "Email: ");
        // getnstr(email, MAX_LEN);
        int val = getstring(stdscr, email, MAX_LEN, 1);
        if(val == 27) {
            clear();
            refresh();
            return 27;
        }
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
        mvprintw((LINES - 7) / 2 + 7, (COLS - 60) / 2 , "%s", "Password(press F1 key to generate random):");
        // getnstr(pass, MAX_LEN);
        int val = getstring(stdscr, pass, MAX_LEN, 0);
        if(val == 27) {
            clear();
            refresh();
            return 27;
        }
        attroff(COLOR_PAIR(4));
        refresh();
        clear();
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
    box(stdscr, 0, 0);
    mvprintw(LINES - 3, 0, "Use arrow keys to navigate and press Enter to select!");
    mvprintw(LINES - 2, 0, "Press Esc key to go to main menu");
    attron(COLOR_PAIR(4));
    mvprintw((LINES - 10) / 2 + 3, (COLS - 30) / 2, "Username : ");
    mvprintw((LINES - 10) / 2 + 5, (COLS - 30) / 2, "Password : ");
    attroff(COLOR_PAIR(4));
    Users *temp = NULL;
    while(1) {
        attron(COLOR_PAIR(4));
        mvprintw((LINES - 10) / 2 + 3, (COLS - 30) / 2, "Username : ");
        mvprintw((LINES - 10) / 2 + 5, (COLS - 30) / 2, "Password : ");
        move((LINES - 10) / 2 + 3, (COLS - 30) / 2 + 11);
        attroff(COLOR_PAIR(4));
        if(temp != NULL) {
            draw_logo(1, "Enter Password for user", 2);
            break;
        }
        // getnstr(username, MAX_LEN);
        int val = getstring(stdscr, username, MAX_LEN, 1);
        if(val == 27) {
            clear();
            refresh();
            return 27;
        }
        temp = check_username(arr, n, username);
        if(temp == NULL) {
            clear();
            draw_logo(1, "User didn't find!", 3);
            refresh();
            continue;
        }
    }
    while (1) {
        attron(COLOR_PAIR(4));
        mvprintw((LINES - 10) / 2 + 5, (COLS - 30) / 2, "Password : ");
        mvprintw((LINES - 10) / 2 + 3, (COLS - 30) / 2, "Username : ");
        attroff(COLOR_PAIR(4));
        mvprintw((LINES - 10) / 2 + 3, (COLS - 30) / 2 + 11, "%s", username);
        move((LINES - 10) / 2 + 5, (COLS - 30) / 2 + 11);
        // getnstr(password, MAX_LEN);
        int val = getstring(stdscr, password, MAX_LEN, 0);
        if(val == 27) {
            clear();
            refresh();
            return 27;
        }
        clear();
        if(!log_in(arr, n, username, password)) {
            draw_logo(1, "Wrong password", 3);
            continue;
        }
        return 1;
    }
}

int pregame_menu() {
    const char *options[] = {" New Game  ", "Resume Game", "ScoreBoard ", " Settings  ", "  Profile  ", "  Log out  "};
    int choose = menu("PreGame menu ", 6, options, 6);
    if(choose == 0) {
        generate_floor();
    }
    else if(choose == 1) {
        
    }
    else if(choose == 2) {
        scoreboard();
    }
    else if(choose == 3) {

    }
    else if(choose == 4) {
        
    }
    else if(choose == 5) {

    }
    else if (choose == -1) {

    }
}
void scoreboard() {
    Users *copy = malloc(MAX_USERS * sizeof(Users));
    memcpy(copy, arr, users_count);
    qsort(copy, users_count, sizeof(Users), compare_score);
    attron(COLOR_PAIR(1) | A_BOLD);
    int startIndex = 0;
    wchar_t first = L'🥇';
    wchar_t second = L'🥈';
    wchar_t third = L'🥉';
    // wchar_t arrow = L'🡒';
    while (1) {
        for(int i = 0; i < 10; i++) {
            attron(COLOR_PAIR(1) | A_BOLD);
            mvprintw((LINES - 20) / 2, (COLS - 77) / 3, "Rank  |  Username  |  TotalScore  |  TotalGold  |  TotalGames  |  Experience");
            attroff(COLOR_PAIR(1) | A_BOLD);
            if(startIndex + i == 0 || 1) {
                mvprintw((LINES - 20) / 2 - (2 * i) - 10, COLS / 3, "%lc     %s | %d | %d | %d | %ld\n", first , copy[i].username, copy[i].score, copy[i].gold, copy[i].games_count, copy[i].start_time);
            }
        }
        refresh();
    }
}

int getstring(WINDOW* win, char* str, int n, int echo) {
    int starty, startx;
    getyx(win, starty, startx);
    noecho();
    curs_set(1);
    char *temp = calloc(n, sizeof(char));
    int count = 0;
    int y, x;
    while(1) {
        int c = wgetch(win);
        if(c == '\n') {
            strncpy(str, temp, count);
            str[count] = 0;
            free(temp);
            curs_set(0);
            return 0;
        }
        else if(c == 27) {
            free(temp);
            curs_set(0);
            return 27;
        }
        else if(c == KEY_BACKSPACE || c == 127) {
        
            getyx(win, y, x);
            if(startx == x)
                continue;
            mvwaddch(win, y, x - 1, ' ');
            wmove(win, y, x - 1);
            count--;
            temp[count] = 0;
            continue;
        }
        else if(c == KEY_F(1) && echo == 0) {
            move(starty, startx);
            for(int i = 0; i < count; i++) {
                printw(" ");
            }
            strcpy(temp, random_password());
            count = strlen(temp);
            mvprintw(starty, startx, "%s", temp);
        }
        else if(count < n - 1 && c >= 32 && c <= 126) {
            if(echo == 0) {
                printw("%c", '*');
            }
            else {
                printw("%c", c);
            }
            temp[count] = c;
            count++;
        }
    }
    curs_set(0);
}
char *random_password() {

    int len = 15 + rand() % 10;
    char *res = malloc((len + 1) * sizeof(char));
    for(int i = 0; i < len; i++) {
        //32  - 126
        res[i] = 32 + rand() % (127 - 32);
    }
    res[len] = 0;
    return res;
}