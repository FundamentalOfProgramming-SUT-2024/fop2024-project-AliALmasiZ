#ifndef _USERS_H
#define _USERS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <time.h>
#include "games.h"


#define MAX_USERS 1000
#define MAX_LEN 50


typedef struct {
    time_t start_time;
    int player_color;
    char username[MAX_LEN];
    char password[MAX_LEN];
    char email[MAX_LEN];
    int score;
    int gold;
    int games_count;
    Floor floors_arr[MAX_FLOORS];
    int active_floor;
    Pos ladders[MAX_FLOORS][2];
    Pos position;
    int under_ch;
    int difficulty;
    Game last_game;
}Users;

int load_users(Users **arr);
void save_users(Users **arr, int users_count);
void sign_up(Users **arr, int *users_count, const char *username, const char *pass, const char *email);
int log_in(Users **arr, int users_count, const char *username, const char *password);
void *check_username(Users **arr, int n, const char *username);
int check_email(char *email);
int pass_check(char *pass);
int compare_score(const void *a, const void *b);
int compare_name(const void *a, const void *b);


extern Users *active_user;
extern Users *arr;
extern int users_count;

#endif