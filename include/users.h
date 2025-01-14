#ifndef USERS_H
#define USERS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

#define MAX_USERS 1000
#define MAX_LEN 256

typedef struct {
    char username[MAX_LEN];
    char password[MAX_LEN];
    char email[MAX_LEN];
    int score;
    int gold;
}Users;

extern int load_users(Users **arr);
extern void save_users(Users **arr, int users_count);
extern void sign_up(Users **arr, int *users_count, const char *username, const char *pass, const char *email);
extern int log_in(Users **arr, int users_count, const char *username, const char *password);
extern void *check_username(Users **arr, int n, const char *username);
extern int check_email(char *email);
extern int pass_check(char *pass);
extern Users *active_user;

#endif