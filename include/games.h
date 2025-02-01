#ifndef _GAME_H
#define _GAME_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

#define MAX_ROOMS 20
#define MAX_FLOORS 4
#define DISTANCE 2
#define MAX_PATH 1000
typedef struct Pos {
    int x;
    int y;
}Pos;
typedef struct Room {
    uint16_t x;
    uint16_t y;
    uint16_t height;
    uint16_t width;
    Pos doors[3];
    uint16_t door_num;
    int door_wall[3];
    uint8_t visible;
}Room;

typedef struct Floor
{
    Room rooms_arr[MAX_ROOMS];
    uint16_t rooms_count;
    Pos hallways[MAX_ROOMS * 4][MAX_PATH];
    uint16_t hallway_count[MAX_ROOMS * 4];
    uint8_t visible[MAX_ROOMS * 4][MAX_PATH];
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
void draw_hallway();
int player_movement();
int resume_game();
int is_in_room(Pos p);

#endif