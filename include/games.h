#ifndef _GAME_H
#define _GAME_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ROOMS 10
#define MAX_FLOORS 4

typedef struct Room {
    int x;
    int y;
    int height;
    int width;
}Room;



extern Room rooms_arr[MAX_FLOORS][MAX_ROOMS];
extern int rooms_count[MAX_FLOORS];
extern int active_floor;

int compare_distance(const void *a, const void *b);
void generate_room();
int can_make(Room r);
void print_rooms();


#endif