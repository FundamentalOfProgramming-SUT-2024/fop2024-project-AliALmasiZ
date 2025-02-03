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

    refresh();
    wattron(menu_win, COLOR_PAIR(1));
    int passchecker = 0;
    while(true) {
        clear();
        if(LINES < 20 || COLS < 40) {
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
            mvwprintw(menu_win, (rows - size) / 2 + i, (cols - strlen(options[i])) / 2, "%s", options[i]);
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
        else if(c == 27) {
            wattroff(menu_win, COLOR_PAIR(1));
            wclear(menu_win);
            clear();
            delwin(menu_win);
            return c;
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
        draw_logo(1 , "Welcome to Rogue", 3);
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
    const char *options[] = {" New Game  ", "Resume Game", "ScoreBoard ", " Settings  "};
    int choose = menu("PreGame menu ", 6, options, 4);
    while (1){
        if(choose == 0) {
            active_floor = 0;
            memset(&active_user->last_game, 0, sizeof(Game));
            active_user->last_game.health = 100;
            active_user->last_game.tools[0] = 1;
            // memset(active_user, 0, MAX_ROOMS * sizeof(Room));
            for(int i = 1; i < 5; i ++) {
                active_user->last_game.tool_floor[i] = rand() % MAX_FLOORS;
            }
            active_floor = 0;
            active_user->active_floor = 0;
            while(active_floor < MAX_FLOORS) 
            {
                clear();
                generate_floor();
                // getch();
                active_floor++;
                active_user->active_floor = active_floor;
            }
            active_user->active_floor = 0;
            active_floor = 0;
            active_user->position.x = active_user->floors_arr[active_floor].rooms_arr[0].x + 1;
            active_user->position.y = active_user->floors_arr[active_floor].rooms_arr[0].y + 1;
            active_user->under_ch = mvinch(active_user->position.x, active_user->position.y);
            init_game();
            resume_game();
            choose = menu("PreGame menu ", 6, options, 4);
        }
        else if(choose == 1) {
            int val = resume_game();
            if(val == 404)
                choose = menu("No Games Found!", 3, options, 4);
            else
                choose = menu("PreGame menu ", 6, options, 4);
        }
        else if(choose == 2) {
            scoreboard();
            choose = menu("PreGame menu ", 6, options, 4);
        }
        else if(choose == 3) {
            const char* settings[] = {"  difficulty  ", "  Hero color  ", "Music Setting "};
            int val = menu("Settings :", 6, settings, 3);
            if (val == 0) {
                const char *diffs[] = {"Easy", "Meduim", "Hard"};
                active_user->difficulty = menu("Select difficalty :", 6, diffs, 3);
                choose = menu("Difficulty has been set!", 6, options, 4);
            }
            else if(val == 1) {
                const char* colors[] = {"White", "  Red  ", " Blue  ", "Magenta", "Yellow ", "Green"}; 

                int color = menu("choose color :", 4, colors, 6);
                if(color == 0) {
                    active_user->player_color = 1;
                }
                else if(color == 1) {
                    active_user->player_color = 3;
                }
                else if(color == 2) {
                    active_user->player_color = 6;
                }
                else if(color == 3) {
                    active_user->player_color = 4;
                }
                else if(color == 4) {
                    active_user->player_color = 12;
                }
                else if(color == 5) {
                    active_user->player_color = 2;
                }
                choose = menu("Player color has been set!", 6, options, 4);
            }
            else if(val == 2) {
                const char *m_settings[] = {"First music", "Second Music", "Music Off"};
                int ms = menu("Select Music :", 3, m_settings, 3);
                
                if(ms == 0) {
                    play_music("./music/first.mp3", 1);
                }
                else if(ms == 1) {
                    
                    play_music("./music/second.mp3", 1);
                }
                else if (ms == 2 || ms == 27) {
                    play_music("", 0);
                } 

                choose = menu("Music Settings have been set!", 6, options, 4);
            }
        }
        else if (choose == -1) {

        }
        else if(choose == 27) {
            return 27;
        }
    }
}
int scoreboard() {
    // mvprintw(3,3, "%s", copy[MAX_USERS].username);
    Users temp = *active_user;
    qsort(arr, users_count, sizeof(Users), compare_score);
    attron(COLOR_PAIR(1) | A_BOLD);
    int startIndex = 0;
    // mvprintw(1, 1, "%s", arr[0].username);
    wchar_t first = L'🥇';
    wchar_t second = L'🥈';
    wchar_t third = L'🥉';
    wchar_t arrow = L'🡒';
    time_t current_time = time(NULL);
    const int max_lines = 10;
    while (1) {
        clear();
        for(int i = 0; i < MIN(users_count, max_lines); i++) {
            int index = i + startIndex;
            // if(active_user == arr + index)            
            if(!strcmp(temp.username, arr[index].username))            
                attron(COLOR_PAIR(3) | A_BOLD | A_ITALIC | A_BLINK);
            // mvprintw((LINES - 20) / 2, (COLS - 77) / 3, "Rank  |                |    |    |    |  ");
            if(index == 0) {
                attron(COLOR_PAIR(12) | A_BOLD);
                mvprintw((LINES - 20) / 2 + (2 * i), (COLS - 77) / 3, "%lc     GOAT :  %s | TotalScore : %d | TotalGold : %d | TotalGames : %d | Experience %ld\n", first , arr[index].username, arr[index].score, arr[index].gold, arr[index].games_count, (current_time - arr[index].start_time));
                attroff(COLOR_PAIR(12) | A_BOLD);
            } 
            else if(index == 1) {
                attron(COLOR_PAIR(10) | A_BOLD);
                mvprintw((LINES - 20) / 2 + (2 * i), (COLS - 77) / 3, "%lc     Shadow :  %s | TotalScore : %d | TotalGold : %d | TotalGames : %d | Experience %ld\n", second , arr[index].username, arr[index].score, arr[index].gold, arr[index].games_count, (current_time - arr[index].start_time));
                attroff(COLOR_PAIR(10) | A_BOLD);
            }
            else if(index == 2) {
                attron(COLOR_PAIR(11) | A_BOLD);
                mvprintw((LINES - 20) / 2 + (2 * i), (COLS - 77) / 3, "%lc     The Fighter :  %s | TotalScore : %d | TotalGold : %d | TotalGames : %d | Experience %ld\n", third , arr[index].username, arr[index].score, arr[index].gold, arr[index].games_count, (current_time - arr[index].start_time));
                attroff(COLOR_PAIR(11) | A_BOLD);
            }
            else {
            
                mvprintw((LINES - 20) / 2 + (2 * i), (COLS - 77) / 3, "%d     Username :  %s | TotalScore : %d | TotalGold : %d | TotalGames : %d | Experience %ld\n", index + 1 , arr[index].username, arr[index].score, arr[index].gold, arr[index].games_count, (current_time - arr[index].start_time));
            
            }
            // if(active_user == arr + index)
            if(!strcmp(temp.username, arr[index].username))
                attroff(COLOR_PAIR(3) | A_BOLD | A_ITALIC | A_BLINK);
        }
        int ch = getch();
        if(ch == KEY_DOWN) {
            if(max_lines + startIndex < users_count)
                startIndex++;
        }
        else if(ch == KEY_UP) {
            if(startIndex > 0) {
                startIndex--;
            }
        }
        else if(ch == 27) {
            return 27;
        }
        refresh();
    }
    qsort(arr, users_count, sizeof(Users), compare_name);

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

    int len = 20 + rand() % 10;
    char *res = malloc((len + 1) * sizeof(char));
    for(int i = 0; i < len; i++) {
        //32  - 126
        res[i] = 32 + rand() % (127 - 32);
    }
    res[len] = 0;
    return res;
}


/*should run with "padsp ./main.out" command*/
int play_music(const char *path, int flag) { 
    static int is_initialized = 0;

    if (!flag) {
        Mix_HaltMusic();
        return 0;
    }

    if (!is_initialized) {
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            clear();
            mvprintw(0, 0, "SDL_Init error: %s\n", SDL_GetError());
            getch();
            return 1;
        }
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            clear();
            mvprintw(0, 0, "Mix_OpenAudio error: %s\n", Mix_GetError());
            getch();
            SDL_Quit();
            return 1;
        }
        is_initialized = 1;
    }
    Mix_HaltMusic();
    Mix_Music *music = Mix_LoadMUS(path);
    if (!music) {
        clear();
        mvprintw(0, 0, "Mix_LoadMUS error: %s\n", Mix_GetError());
        getch();
        return 1;
    }

    if (Mix_PlayMusic(music, -1) == -1) {
        clear();
        mvprintw(0, 0, "Mix_PlayMusic error: %s\n", Mix_GetError());
        getch();
        Mix_FreeMusic(music);
        return 1;
    }

    Mix_VolumeMusic(120);
    
    return 0;
}