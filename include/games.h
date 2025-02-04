#ifndef _GAME_H
#define _GAME_H

// #define _GNU_SOURCE
#include <ncursesw/ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

#define MAX_ROOMS 20
#define MAX_FLOORS 4
#define DISTANCE 3
#define MAX_PATH 1000




#define message(s, attr) do {      \
    clear_messageBox();         \
    attron((attr));         \
    mvprintw(0, 0, "%s", (s));      \
    attroff((attr));           \
} while(0)




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

typedef struct Enemy {
    Pos position;
    uint8_t is_active : 1;
    uint8_t floor : 3;
    uint8_t followed : 3;
    uint8_t room_ind : 5;
    uint8_t type : 3;
    int8_t health;

} Enemy;
typedef struct Game {
    uint16_t gold;
    int8_t health;
    uint8_t food[4];
    uint8_t active_tool : 3;
    uint8_t speed_count : 3;
    uint8_t damage_count : 3;
    uint8_t health_count : 3;
    int8_t hunger;
    uint8_t tools[5];
    Pos gold_loc[MAX_FLOORS][3];
    Pos tool_location[5];
    uint8_t tool_floor[5];
    Pos food_loc[MAX_FLOORS][MAX_ROOMS];
    uint8_t food_type[MAX_FLOORS][MAX_ROOMS];
    Pos speed_loc[MAX_FLOORS];
    Pos damage_loc[MAX_FLOORS];
    Pos health_loc[MAX_FLOORS];
    Pos trap_loc[MAX_FLOORS];
    Room treasure;
    Enemy enemies[MAX_FLOORS][3];


} Game;

extern Room rooms_arr[MAX_FLOORS][MAX_ROOMS];
extern int rooms_count[MAX_FLOORS];
extern int active_floor;
extern Game g;
extern const char *tools_name[];

int compare_distance(const void *a, const void *b);
void generate_room();
int can_make(Room r);
void print_rooms(int flag);
void connect_rooms();
void connect_doors();
void generate_floor();
void print_floor();
void draw_hallway();
int player_movement();
int resume_game();
int is_in_rooms(Pos p);
void print_elements();
int init_game();
void print_treasure();
void clear_messageBox();
int food_menu();
int enchant_menu();
int tool_menu();

#endif