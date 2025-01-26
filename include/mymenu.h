#ifndef MENU_H
#define MENU_H
#include "users.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>


int menu(char* message, int color, const char **options, int size);
void goodbye_logo();
int sign_up_menu(Users **arr, int *n);
void draw_logo(int y, char *message, int color_pair);
int login_menu(Users **arr, int n);
int pregame_menu();
void scoreboard();
int getstring(WINDOW* win, char* str, int n, int echo);
char *random_password();


#endif





