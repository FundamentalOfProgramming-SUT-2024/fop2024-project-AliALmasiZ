#ifndef MENU_H
#define MENU_H
#include "users.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>


extern int init_menu(char* message, int color);
extern void goodbye_logo();
extern int sign_in_menu(Users **arr, int *n);
extern void draw_logo(int y, char *message, int color_pair);
    
#endif





