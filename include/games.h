#ifndef _GAME_H
#define _GAME_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#define MAX_ROOMS 10
#define MAX_FLOORS 4
#define DISTANCE 2
#define MAX_PATH 10000
typedef struct Pos {
    int x;
    int y;
}Pos;
typedef struct Room {
    int x;
    int y;
    int height;
    int width;
    Pos doors[3];
    int door_num;
    int door_wall[3];
    int visible;
}Room;

typedef struct Floor
{
    Room rooms_arr[MAX_ROOMS];
    int rooms_count;
    Pos hallways[MAX_ROOMS][MAX_PATH];
    int hallway_count[MAX_ROOMS];
} Floor;


extern Room rooms_arr[MAX_FLOORS][MAX_ROOMS];
extern int rooms_count[MAX_FLOORS];
extern int active_floor;

int compare_distance(const void *a, const void *b);
void generate_room();
int can_make(Room r);
void print_rooms();
void connect_rooms();
void connect_doors();
void generate_floor();
void print_floor();

#endif