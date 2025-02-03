#ifndef MENU_H
#define MENU_H
#include "users.h"
// #define _GNU_SOURCE
#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int menu(char* message, int color, const char **options, int size);
void goodbye_logo();
int sign_up_menu(Users **arr, int *n);
void draw_logo(int y, char *message, int color_pair);
int login_menu(Users **arr, int n);
int pregame_menu();
int scoreboard();
int getstring(WINDOW* win, char* str, int n, int echo);
char *random_password();
int play_music(const char * path, int flag);

#endif





