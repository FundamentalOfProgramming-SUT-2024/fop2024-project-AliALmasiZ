#ifndef USERS_H
#define USERS_H

#define MAX_USERS 1000
#define MAX_SIZE 256

typedef struct {
    char username[MAX_SIZE];
    char password[MAX_SIZE];
    char email[MAX_SIZE];
    int score;
    int gold;
}Users;

extern int load_users(Users **arr);
extern void save_users(Users **arr, int *users_count);
extern void sign_in(Users **arr, int *users_count, const char *username, const char *pass, const char *email);
extern int log_in(Users **arr, int *uesrs_count, const char *username, const char *password);

#endif