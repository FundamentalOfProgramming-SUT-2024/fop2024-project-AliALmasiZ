#include "../include/games.h"

Room rooms_arr[MAX_FLOORS][MAX_ROOMS] = {0};
int rooms_count[MAX_FLOORS] = {0};
int active_floor = 0;
void generate_room() {
    int x1, width, y1, height;
    width = rand() % 12 + 5;
    height = rand() % 8 + 5;
    x1 = rand() % (COLS - width - 1) + 1;
    y1 = rand() % (LINES - height - 1) + 1;
    rooms_arr[active_floor][rooms_count[active_floor]].x = x1;
    rooms_arr[active_floor][rooms_count[active_floor]].y = y1;
    rooms_arr[active_floor][rooms_count[active_floor]].height = height;
    rooms_arr[active_floor][rooms_count[active_floor]].width = width;
    if(can_make(rooms_arr[active_floor][rooms_count[active_floor]])) {
        rooms_count[active_floor]++;
    }
}

int can_make(Room r) {
    for(int i = 0; i < rooms_count[active_floor]; i++) {
        if(rooms_arr[active_floor][i].x <= r.x && rooms_arr[active_floor][i].x + rooms_arr[active_floor][i].width >= r.x) {
            if(
                (rooms_arr[active_floor][i].y <= r.y + r.height && rooms_arr[active_floor][i].y + rooms_arr[active_floor][i].height >= r.y + r.height) ||
                (rooms_arr[active_floor][i].y <= r.y && rooms_arr[active_floor][i].y + rooms_arr[active_floor][i].height >= r.y)
            )
                return 0;
        }
        else if(rooms_arr[active_floor][i].x <= r.x + r.width && rooms_arr[active_floor][i].x + rooms_arr[active_floor][i].width >= r.x + r.width) {
            if(
                (rooms_arr[active_floor][i].y <= r.y + r.height && rooms_arr[active_floor][i].y + rooms_arr[active_floor][i].height >= r.y + r.height) ||
                (rooms_arr[active_floor][i].y <= r.y && rooms_arr[active_floor][i].y + rooms_arr[active_floor][i].height >= r.y)
            )
                return 0;
        }
    }
    return 1;
}
int compare_distance(const void *a, const void *b) {
    int x2, y2;
    Room *a1, *b1;
    a1 = (Room *)a;
    b1 = (Room *)b;
    x2 = (a1->x + a1->width / 2) - (b1->x + b1->width / 2);
    y2 = (a1->y + a1->height / 2) - (b1->y + b1->height / 2);
    return x2 + y2;
}
void print_rooms() {
    qsort(rooms_arr[active_floor], MAX_ROOMS, sizeof(Room), compare_distance);
    attron(A_BOLD);
    for(int i = 0; i < rooms_count[active_floor]; i++) {
        for(int j = rooms_arr[active_floor][i].x; j <= rooms_arr[active_floor][i].x + rooms_arr[active_floor][i].width; j++) {
            for(int k = rooms_arr[active_floor][i].y; k <= rooms_arr[active_floor][i].y + rooms_arr[active_floor][i].height; k++) {
                if(k == rooms_arr[active_floor][i].y || k == rooms_arr[active_floor][i].y + rooms_arr[active_floor][i].height)
                    mvaddch(k, j, ACS_HLINE);
                else if(j == rooms_arr[active_floor][i].x || j == rooms_arr[active_floor][i].x + rooms_arr[active_floor][i].width)
                    mvaddch(k, j, ACS_VLINE);
                else
                    mvaddch(k, j, '.');
            }
        }
        mvaddch(rooms_arr[active_floor][i].y, rooms_arr[active_floor][i].x, ACS_ULCORNER);
        mvaddch(rooms_arr[active_floor][i].y, rooms_arr[active_floor][i].x + rooms_arr[active_floor][i].width, ACS_URCORNER);
        mvaddch(rooms_arr[active_floor][i].y + rooms_arr[active_floor][i].height, rooms_arr[active_floor][i].x, ACS_LLCORNER);
        mvaddch(rooms_arr[active_floor][i].y + rooms_arr[active_floor][i].height, rooms_arr[active_floor][i].x + rooms_arr[active_floor][i].width, ACS_LRCORNER);
    }
    attroff(A_BOLD);
}