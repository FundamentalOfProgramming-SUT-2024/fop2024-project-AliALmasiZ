#include "../include/users.h"


int compare_name(const void *a, const void *b) {
    return strcmp((*(Users *)a).username, (*(Users *)b).username);
}
int compare_score(const void *a, const void *b) {
    return -(*(Users*)a).score + (*(Users*)b).score;
}
int load_users(Users **arr) {
    FILE *usersfile = fopen("users.bin", "rb");
    if(usersfile == NULL)
        return 0;
    fseek(usersfile, 0, SEEK_SET);
    if(usersfile == NULL) {
        return 0;
    }
    int i = 0;
    while(fread(*arr + i, sizeof(Users), 1, usersfile) == 1){
        i++;
    }
    fclose(usersfile);
    return i;
}
void save_users(Users **arr, int users_count) {
    qsort(*arr, users_count, sizeof(Users), compare_name);
    FILE *usersfile = fopen("users.bin", "wb");
    fseek(usersfile, 0, SEEK_SET);
    // for(int i = 0; i < users_count; i++) {
        // fwrite(*arr + i, sizeof(Users), 1, usersfile);
    // }
    fwrite(*arr, sizeof(Users) * users_count, 1, usersfile);
    fclose(usersfile);
}
void sign_up(Users **arr, int *users_count, const char *username, const char *pass, const char *email) {
    strcpy((*arr + *users_count)->email, email);
    strcpy((*arr + *users_count)->username, username);
    strcpy((*arr + *users_count)->password, pass);
    (*arr + *users_count)->start_time = time(NULL);
    (*arr + *users_count)->player_color = 1;
    (*arr + *users_count)->difficulty = 1;
    
    (*users_count)++;
    save_users(arr, *users_count);
}
int log_in(Users **arr, int users_count, const char *username, const char *password) {
    Users *temp = (Users *)check_username(arr, users_count, username);
    if(strcmp(password, temp->password)) {
        return 0;
    }
    else {
        active_user = temp;
        return 1;        
    }
}

void *check_username(Users **arr, int n, const char *username) {
    qsort(*arr, users_count, sizeof(Users), compare_name);
    Users temp;
    strcpy(temp.username, username);
    return bsearch(&temp, *arr, n, sizeof(Users), compare_name);
}

int check_email(char *email) {
    regex_t regex;
    int num;
    regcomp(&regex, "^[a-zA-Z0-9_]+@[a-zA-Z0-9]+\\.[a-zA-Z]+$", REG_EXTENDED);
    num = regexec(&regex, email, 0, NULL, 0);
    if(num == REG_NOMATCH) {
        return 0;
    }
    else if(num == 0) {
        return 1;
    }
    else {
        return -1;
    }
}
int pass_check(char *pass) {
    struct Flags
    {
        unsigned int len : 1;
        unsigned int upper : 1;
        unsigned int lower : 1;
        unsigned int digit : 1;
    };
    struct Flags flags = {0,0,0,0};
    for(int i = 0; pass[i] != '\0'; i++) {
        if(isdigit(pass[i])) {
            flags.digit = 1;
        }
        if(islower(pass[i])) {
            flags.lower = 1;
        }
        if(isupper(pass[i])) {
            flags.upper = 1;
        }
        if(i > 5) {
            flags.len = 1;
        }
    }
    return flags.len * 8 + flags.digit * 4 + flags.upper * 2 + flags.lower;
}


