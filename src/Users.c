#include "users.h"
#include <stdlib.h>
#include <stdio.h>

int load_users(Users **arr) {
    FILE *usersfile = fopen("users.bin", "rb");
    int i = 0;
    while(fread(arr + i, sizeof(Users), 1, usersfile) == 1) {i++;}
    return i;
}
void save_users(Users **arr, int *users_count) {
    FILE *usersfile = fopen("users.bin", "wb");
    for(int i = 0; i < *users_count; i++) {
        fwrite(arr + i, sizeof(Users), 1, usersfile);
    }
}
void sign_in(Users **arr, int *users_count, const char *username, const char *pass, const char *email) {

}
int log_in(Users **arr, int *uesrs_count, const char *username, const char *password) {

}
