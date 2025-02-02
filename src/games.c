#include "../include/games.h"
#include "../include/users.h"
Room rooms_arr[MAX_FLOORS][MAX_ROOMS] = {0};
int rooms_count[MAX_FLOORS] = {0};
int active_floor = 0;
Floor *floors_arr;
Pos visited[MAX_PATH] = {};
int visited_count = 0;
int is_visible = 0;
Room ladder_room;
Game g = {};

const char* Mace = "⚒"; // 0
const char* Dagger = "\U0001F5E1"; // 1
const char* Magic_wand = "\U0001FA84"; // 2
const char* Normal_arrow = "\u27B3"; // 3
const char* Sword = "\u2694"; // 4
const char *tools_icon[] = {"⚒", "\U0001F5E1", "\U0001FA84", "\u27B3", "\u2694"};

const char* health_p = "\u2764";// 0
const char* speed_p = "\u26A1"; // 1
const char* damage_p = "\u2620"; // 2
const char* enchant_icons[] = {"\u2764", "\u26A1", "\u2620"};

void generate_room() {

    int x1, width, y1, height;
    width = rand() % 15 + 5;
    height = rand() % 6 + 5;
    x1 = rand() % (COLS - width - 1) + DISTANCE + 1;
    y1 = rand() % (LINES - height - 1) + DISTANCE + 1;
    if(x1 + width + DISTANCE>= COLS || y1 + height + DISTANCE >= LINES) {
        return;
    }
    rooms_arr[active_floor][rooms_count[active_floor]].x = x1;
    rooms_arr[active_floor][rooms_count[active_floor]].y = y1;
    rooms_arr[active_floor][rooms_count[active_floor]].height = height;
    rooms_arr[active_floor][rooms_count[active_floor]].width = width;
    rooms_arr[active_floor][rooms_count[active_floor]].visible = 0;
    if(can_make(rooms_arr[active_floor][rooms_count[active_floor]])) {
        rooms_arr[active_floor][rooms_count[active_floor]].door_num = rand() % 3 + 1;
        for(int i = 0; i < rooms_arr[active_floor][rooms_count[active_floor]].door_num; i++) {
            rooms_arr[active_floor][rooms_count[active_floor]].door_wall[i] = rand() % 4;
            switch (rooms_arr[active_floor][rooms_count[active_floor]].door_wall[i]) {
            case 0:
                rooms_arr[active_floor][rooms_count[active_floor]].doors[i].x = rand() % (width - 1) + 1;
                rooms_arr[active_floor][rooms_count[active_floor]].doors[i].y = 0;
                break;
            
            case 1:
                rooms_arr[active_floor][rooms_count[active_floor]].doors[i].x = width;
                rooms_arr[active_floor][rooms_count[active_floor]].doors[i].y = rand() % (height - 1) + 1;
                break;

            case 2:
                rooms_arr[active_floor][rooms_count[active_floor]].doors[i].x = rand() % (width - 1) + 1;
                rooms_arr[active_floor][rooms_count[active_floor]].doors[i].y = height;
                break;

            case 3: 
                rooms_arr[active_floor][rooms_count[active_floor]].doors[i].x = 0;
                rooms_arr[active_floor][rooms_count[active_floor]].doors[i].y = rand() % (height - 1) + 1;
                break;

            default:
                break;
            }
        }
        rooms_count[active_floor]++;
    }
}


int can_make(Room r) {
    for(int i = 0; i < rooms_count[active_floor]; i++) {
        if(
            (rooms_arr[active_floor][i].x <= DISTANCE + r.x && rooms_arr[active_floor][i].x + rooms_arr[active_floor][i].width + DISTANCE>= r.x )||
            (rooms_arr[active_floor][i].x <= DISTANCE + r.x + r.width && rooms_arr[active_floor][i].x + rooms_arr[active_floor][i].width + DISTANCE>= r.x + r.width)
        ) {
            /*if(
                (rooms_arr[active_floor][i].y <= r.y + r.height && rooms_arr[active_floor][i].y + rooms_arr[active_floor][i].height >= r.y + r.height) ||
                (rooms_arr[active_floor][i].y <= r.y && rooms_arr[active_floor][i].y + rooms_arr[active_floor][i].height >= r.y)
            )
                return 0;*/
            if(
                (rooms_arr[active_floor][i].y + DISTANCE>= r.y && rooms_arr[active_floor][i].y <= DISTANCE + r.y + r.height )||
                (rooms_arr[active_floor][i].y <= DISTANCE + r.y && rooms_arr[active_floor][i].y + rooms_arr[active_floor][i].height + DISTANCE>= r.y)
            )
                return 0;
        }   
        if(
            (rooms_arr[active_floor][i].y <= DISTANCE + r.y && rooms_arr[active_floor][i].y + rooms_arr[active_floor][i].height + DISTANCE>= r.y) ||
            (rooms_arr[active_floor][i].y <= DISTANCE + r.y + r.height && rooms_arr[active_floor][i].y + rooms_arr[active_floor][i].height + DISTANCE>= r.y + r.height)
        ) {
            /*if(
                (rooms_arr[active_floor][i].y <= r.y + r.height && rooms_arr[active_floor][i].y + rooms_arr[active_floor][i].height >= r.y + r.height) ||
                (rooms_arr[active_floor][i].y <= r.y && rooms_arr[active_floor][i].y + rooms_arr[active_floor][i].height >= r.y)
            )
                return 0;*/
            if(
                rooms_arr[active_floor][i].x + DISTANCE >= r.x && rooms_arr[active_floor][i].x <=DISTANCE + r.x + r.width ||
                rooms_arr[active_floor][i].x <=DISTANCE + r.x && rooms_arr[active_floor][i].x + rooms_arr[active_floor][i].width + DISTANCE >= r.x

            )
                return 0;
        }
    }
    return 1;
}
int compare_distance(const void *a, const void *b) {
    int x2, y2;
    const Room *a1, *b1;
    a1 = (const Room *)a;
    b1 = (const Room *)b;
    x2 = (a1->x + a1->width / 2) - (b1->x + b1->width / 2);
    y2 = (a1->y + a1->height / 2) - (b1->y + b1->height / 2);
    return x2 + y2;
}
void print_rooms(int flag) {
    // qsort(rooms_arr[active_floor], MAX_ROOMS, sizeof(Room), compare_distance);
    attron(A_BOLD);
    for(int i = 0; i < rooms_count[active_floor]; i++) {
        Room temp = rooms_arr[active_floor][i];
        if(temp.visible == 0 && flag == 0)
            continue;
        for(int j = temp.x; j <= temp.x + temp.width; j++) {
            for(int k = temp.y; k <= temp.y + temp.height; k++) {
                if(k == temp.y || k == temp.y + temp.height)
                    mvaddch(k, j, ACS_HLINE);
                else if(j == temp.x || j == temp.x + temp.width)
                    mvaddch(k, j, ACS_VLINE);
                else
                    mvaddch(k, j, '.');
            }
        }
        mvaddch(temp.y, temp.x, ACS_ULCORNER);
        mvaddch(temp.y, temp.x + temp.width, ACS_URCORNER);
        mvaddch(temp.y + temp.height, temp.x, ACS_LLCORNER);
        mvaddch(temp.y + temp.height, temp.x + temp.width, ACS_LRCORNER);
        for(int j = 0; j < temp.door_num || temp.door_wall[j] == -1; j++) {
            mvaddch(temp.y + temp.doors[j].y, temp.x + temp.doors[j].x, '+');
        }
    }
    if((mvinch(active_user->ladders[active_floor][1].y, active_user->ladders[active_floor][1].x) & A_CHARTEXT) != ' ')
        mvprintw(active_user->ladders[active_floor][1].y, active_user->ladders[active_floor][1].x, "<");
    if((mvinch(active_user->ladders[active_floor][0].y, active_user->ladders[active_floor][0].x) & A_CHARTEXT) != ' ')
        mvprintw(active_user->ladders[active_floor][0].y, active_user->ladders[active_floor][0].x, ">");
    mvprintw(0, 0, " ");
    attroff(A_BOLD);
}

int is_overlap(int x, int y) {
    chtype ch = mvinch(y, x);
    ch &= A_CHARTEXT;
    if(ch == (ACS_ULCORNER & A_CHARTEXT) || ch == (ACS_LLCORNER & A_CHARTEXT) || ch == (ACS_LRCORNER & A_CHARTEXT) || ch == (ACS_URCORNER & A_CHARTEXT) ||
     ch == (ACS_HLINE & A_CHARTEXT) || ch == (ACS_VLINE & A_CHARTEXT) || ch == '.' || ch =='+'
    )
        return 1;
    return 0;

}
int is_visited(int x, int y) {
    for(int i = 0; i < visited_count; i++) {
        if(x == visited[i].x && y == visited[i].y) {
            return 1;
        }
    }
    return 0;
}

int make_hallway(int start_x, int start_y, int end_x, int end_y) {
    if(start_y < end_y) {
        int temp = start_y;
        start_y = end_y;
        end_y = temp;

        temp = start_x;
        start_x = end_x;
        end_x = temp;
    }
    int dx, dy;
    Pos current = {start_x, start_y};
    visited_count = 0;
    int flag;
    while(1) {    
        visited[visited_count++] = current;
        if (visited_count >= MAX_PATH - 1) {
            refresh();
            getch();
            printf("Error: Exceeded MAX_PATH in make_hallway()!\n");
            return 0;
        }
        if((abs(end_x - current.x) <= 1 && end_y == current.y) || (abs(end_y - current.y) <= 1 && end_x == current.x))
            return 1;
        if(current.x == end_x && current.y == end_y)
            return 1;
        dx = (end_x > current.x) ? 1 : (end_x < current.x) ? -1 : 0;
        dy = (end_y > current.y) ? 1 : (end_y < current.y) ? -1 : 0;

        if(dy != 0 && !is_overlap(current.x, current.y + dy) && !is_visited(current.x, current.y + dy)) {
            flag = 1;
            current.y += dy;
            mvaddch(current.y, current.x, '#');
            // refresh();
            // getch();
            continue;
            
        }
        if(dx != 0 && !is_overlap(current.x + dx, current.y) && !is_visited(current.x + dx, current.y)) {
            flag = 0;
            current.x += dx;
            mvaddch(current.y, current.x, '#');
            // refresh();
            // getch();
            continue;
        }
        Pos moves[4];
        if(dy == 0) {
            moves[0] = (Pos){current.x, current.y - 1};
            moves[1] = (Pos){current.x, current.y + 1};
            moves[2] = (Pos){current.x + 1, current.y};
            moves[3] = (Pos){current.x - 1, current.y};
        }
        else if(dx == 0) {
            moves[0] = (Pos){current.x + 1, current.y};
            moves[1] = (Pos){current.x - 1, current.y};
            moves[2] = (Pos){current.x, current.y - 1};
            moves[3] = (Pos){current.x, current.y + 1};
        }
        else {
            if(flag == 1) {
                moves[0] = (Pos){current.x, current.y + 1};
                moves[1] = (Pos){current.x, current.y - 1};
                moves[2] = (Pos){current.x - 1, current.y};
                moves[3] = (Pos){current.x + 1, current.y};
                flag = 1;
            }
            else {
                moves[0] = (Pos){current.x + 1, current.y};
                moves[1] = (Pos){current.x - 1, current.y};
                moves[2] = (Pos){current.x, current.y - 1};
                moves[3] = (Pos){current.x, current.y + 1};
                flag = 0;   
            }
        }
        int found = 0;
        for(int i = 0; i < 4; i++) {
            if(!is_overlap(moves[i].x, moves[i].y) && !is_visited(moves[i].x, moves[i].y)) {
                if(i == 0 || i == 1) {
                    if(dy == 0 || flag == 1)
                        flag = 1;
                    else 
                        flag = 0;
                }
                else {
                    if(dy == 0 || flag == 1)
                        flag = 0;
                    else 
                        flag = 1;
                }
                current = moves[i];
                mvaddch(current.y, current.x, '#');
                // refresh();
                // getch();
                found = 1;
                break;
            }
        }
        if(!found) {
            current = visited[visited_count - 2];
            visited_count -= 2;
            continue;
        }
        // return 0;
    }
}

void connect_doors() {
    int fuck = 0;

    qsort(rooms_arr[active_floor], rooms_count[active_floor], sizeof(Room), compare_distance);
    for (int i = 0; i < rooms_count[active_floor] - 1; i++) {
        Room room1 = rooms_arr[active_floor][i];
        Room room2 = rooms_arr[active_floor][i + 1];
        for (int j = 0; j < room1.door_num && j < room2.door_num; j++){
            if((room1.door_wall[j] == -1 || room2.door_wall[j] == -1) && j != 0)
                continue;
            if(room1.x == 0 || room2.x == 0)
                continue;
            if(j >= room1.door_num || j >= room2.door_num)
                continue;
            int door1_x = room1.x + room1.doors[j].x;
            int door1_y = room1.y + room1.doors[j].y;
            int door2_x = room2.x + room2.doors[j].x;
            int door2_y = room2.y + room2.doors[j].y;
            if(door1_x == 0 || door2_x == 0 || door1_x == 1 || door2_x == 1)
                continue;
            room1.door_wall[j] = -1;
            room2.door_wall[j] = -1;
            visited_count = 0;
            if(floors_arr == NULL)
                printf("floors_arr unallocated!\n");
            // attron(COLOR_PAIR((fuck) % 2 + 1));
            make_hallway(door1_x, door1_y, door2_x, door2_y);
            // memset(floors_arr[active_floor].hallways[3 * i + j], 0, MAX_PATH);
            memcpy(floors_arr[active_floor].hallways[3 * i + j], visited, visited_count * sizeof(Pos));
            floors_arr[active_floor].hallway_count[3 * i + j] = visited_count;
            // attroff(COLOR_PAIR((fuck++) % 2 + 1));
        }
        
    }
}
void add_tools() {
    for(int i = 1; i < 5; i++) {
        g.tool_floor[i] = rand() % MAX_FLOORS;
        int ind = rand() % rooms_count[g.tool_floor[i]];
        int x = rand() % (rooms_arr[g.tool_floor[i]][ind].width - 2) + 1 + rooms_arr[g.tool_floor[i]][ind].x;
        int y = rand() % (rooms_arr[g.tool_floor[i]][ind].height - 1) + 1 + rooms_arr[g.tool_floor[i]][ind].y;
        Pos temp = {x, y};
        g.tool_location[i] = temp;
    }
}
void print_tools() {
    for(int i = 1; i < 5; i++) {
        if(active_floor != g.tool_floor[i])
            continue;
        Pos temp = g.tool_location[i];
        if(temp.x != 0 && temp.y != 0 && (mvinch(temp.y, temp.x) & A_CHARTEXT) == '.')
            mvprintw(temp.y, temp.x, "%s", tools_icon[i]);
    }
}
void add_enchant() 
{
    for(int i = 0; i < MAX_FLOORS; i++) {
        int ind = rand() % rooms_count[g.tool_floor[i]];
        int x = rand() % (rooms_arr[g.tool_floor[i]][ind].width - 2) + 1 + rooms_arr[g.tool_floor[i]][ind].x;
        int y = rand() % (rooms_arr[g.tool_floor[i]][ind].height - 1) + 1 + rooms_arr[g.tool_floor[i]][ind].y;
        Pos temp = {x, y};
        g.damage_loc[i] = temp;
    }
    for(int i = 0; i < MAX_FLOORS; i++) {
        int ind = rand() % rooms_count[g.tool_floor[i]];
        int x = rand() % (rooms_arr[g.tool_floor[i]][ind].width - 2) + 1 + rooms_arr[g.tool_floor[i]][ind].x;
        int y = rand() % (rooms_arr[g.tool_floor[i]][ind].height - 1) + 1 + rooms_arr[g.tool_floor[i]][ind].y;
        Pos temp = {x, y};
        g.speed_loc[i] = temp;
    }
    for(int i = 0; i < MAX_FLOORS; i++) {
        int ind = rand() % rooms_count[g.tool_floor[i]];
        int x = rand() % (rooms_arr[g.tool_floor[i]][ind].width - 2) + 1 + rooms_arr[g.tool_floor[i]][ind].x;
        int y = rand() % (rooms_arr[g.tool_floor[i]][ind].height - 1) + 1 + rooms_arr[g.tool_floor[i]][ind].y;
        Pos temp = {x, y};
        g.health_loc[i] = temp;
    }
}
void print_enchants() {
    Pos temp = g.health_loc[active_floor];
    if(temp.x != 0 && temp.y != 0 && (mvinch(temp.y, temp.x) & A_CHARTEXT) == '.')
        mvprintw(temp.y, temp.x, "%s", enchant_icons[0]);
    temp = g.speed_loc[active_floor];
    if(temp.x != 0 && temp.y != 0 && (mvinch(temp.y, temp.x) & A_CHARTEXT) == '.')
        mvprintw(temp.y, temp.x, "%s", enchant_icons[1]);
    temp = g.damage_loc[active_floor];
    if(temp.x != 0 && temp.y != 0 && (mvinch(temp.y, temp.x) & A_CHARTEXT) == '.')
        mvprintw(temp.y, temp.x, "%s", enchant_icons[2]);
}

void add_golds() {
    for(int i = 0; i < MAX_FLOORS; i++) {
        for(int j = 0; j < 3; j++) {
            int ind = rand() % rooms_count[i];
            int x = rand() % (rooms_arr[i][ind].width - 2) + 1 + rooms_arr[i][ind].x;
            int y = rand() % (rooms_arr[i][ind].height - 1) + 1 + rooms_arr[i][ind].y;
            Pos temp = {x, y};
            g.gold_loc[i][j] = temp;
        }
    }
}
void print_gold() {
    attron(COLOR_PAIR(12));
    for(int i = 0; i < MAX_FLOORS; i++) {
        for(int j = 0; j < 2; j++) {
            if(g.gold_loc[i][j].y != 0 && g.gold_loc[i][j].x != 0)
                mvprintw(g.gold_loc[i][j].y, g.gold_loc[i][j].x, "$");
        }
    }
    attroff(COLOR_PAIR(12));
    attron(COLOR_PAIR(7) | A_BOLD);
    for(int i = 0; i < MAX_FLOORS; i++) {
        if(g.gold_loc[i][2].y != 0 && g.gold_loc[i][2].x != 0)
                mvprintw(g.gold_loc[i][2].y, g.gold_loc[i][2].x, "$");
    }
    attroff(COLOR_PAIR(7) | A_BOLD);
    
}
void add_foods() {
    for(int i = 0; i < MAX_FLOORS; i++) {
        for(int j = 0; j < rooms_count[i]; j++) 
        {
            int x = rand() % (rooms_arr[i][j].width - 2) + 1 + rooms_arr[i][j].x;
            int y = rand() % (rooms_arr[i][j].height - 1) + 1 + rooms_arr[i][j].y;
            Pos temp = {x, y};
            g.food_loc[i][j] = temp;
        }
    }
}
void print_foods() {
    for(int i = 0; i < MAX_FLOORS; i++) 
    {
        for(int j = 0; j < rooms_count[i]; j++) 
        {
            if(g.food_loc[i][j].y != 0 && g.food_loc[i][j].x)
                mvprintw(g.food_loc[i][j].y, g.food_loc[i][j].x, "f");
        }
    }
}

void print_elements() 
{
    
}

void generate_floor() {
    floors_arr = active_user->floors_arr;
    // memset(floors_arr[active_floor].rooms_arr, 0, MAX_ROOMS * sizeof(Room));
    memset(&floors_arr[active_floor], 0, sizeof(Floor));
    int counter = 0;
    rooms_count[active_floor] = 0;
    if(active_floor > 0) {
        rooms_arr[active_floor][0] = ladder_room;
        rooms_count[active_floor]++;
    }
    while(rooms_count[active_floor] < 6 || counter < 20) {
        counter++;
        generate_room();
    }
    if(active_floor > 0) {
        active_user->ladders[active_floor][0] = active_user->ladders[active_floor - 1][1];
    }
    if(active_floor < MAX_FLOORS - 1 && active_floor != 0) {
        ladder_room = rooms_arr[active_floor][rooms_count[active_floor] - 1];
        active_user->ladders[active_floor][1].x = ladder_room.x + rand() % (ladder_room.width - 1) + 1;
        active_user->ladders[active_floor][1].y = ladder_room.y + rand() % (ladder_room.height - 1) + 1;
        ladder_room.visible = 1;
    }
    floors_arr[active_floor].rooms_count = rooms_count[active_floor];
    memcpy(floors_arr[active_floor].rooms_arr, rooms_arr[active_floor], rooms_count[active_floor] * sizeof(Room));
    qsort(floors_arr[active_floor].rooms_arr, rooms_count[active_floor], sizeof(Room), compare_distance);
    
    print_rooms(1);

    add_tools();

    connect_doors();
    if(active_floor == 0) {
        ladder_room = rooms_arr[active_floor][rooms_count[active_floor] - 1];
        active_user->ladders[active_floor][1].x = ladder_room.x + rand() % (ladder_room.width - 1) + 1;
        active_user->ladders[active_floor][1].y = ladder_room.y + rand() % (ladder_room.height - 1) + 1;
        ladder_room.visible = 1;
    }
    // refresh();
    // getch();
    
}


void print_message_box() {
    attron(COLOR_PAIR(12));
    for(int i = 0; i < COLS; i++) {
        mvaddch(2, i, ACS_HLINE);
    }
    attroff(COLOR_PAIR(12));
    attron(COLOR_PAIR(6) | A_BOLD);
    mvprintw(1, COLS - 13, "Golds : %d ", g.gold);
    mvprintw(1, 0, "Health : %d %% hunger : %d %% foods in inventory: %d", g.health, g.hunger, g.food);
    attroff(COLOR_PAIR(6) | A_BOLD);

}
void print_floor() {
    clear();
    floors_arr = active_user->floors_arr;
    rooms_count[active_floor] = floors_arr[active_floor].rooms_count;
    memcpy(rooms_arr[active_floor], floors_arr[active_floor].rooms_arr, rooms_count[active_floor] * sizeof(Room));
    print_message_box();
    draw_hallway();
    print_rooms(is_visible);

}
void check_hallway(int i, int j, Pos player) {
    Pos hallway = floors_arr[active_floor].hallways[i][j];
    if((active_user->under_ch & A_CHARTEXT) == '#' || (active_user->under_ch & A_CHARTEXT) == '+')
        if(
        (abs(player.x - hallway.x) <= 3 && abs(player.y - hallway.y) <= 1) ||
        (abs(player.x - hallway.x) <= 1 && abs(player.y - hallway.y) <= 3)
        ) {
            floors_arr[active_floor].visible[i][j] = 1;
        }
    
}
void draw_hallway() {
    for(int i = 0; i < MAX_ROOMS * 4; i++) {
        for(int j = 0; j < floors_arr[active_floor].hallway_count[i]; j++) {
            check_hallway(i, j, active_user->position);
            if(floors_arr[active_floor].visible[i][j] == 0 && is_visible == 0)
                continue;
            Pos current = floors_arr[active_floor].hallways[i][j];
            if((mvinch(current.y, current.x) & A_CHARTEXT) != '+')
                mvaddch(current.y, current.x, '#');
        }
    }
}

int player_movement() {
    rooms_arr[0][0].visible = 1;
    floors_arr[0].rooms_arr[0].visible = 1;

    Pos *current = &active_user->position;
    int next_ch = mvinch(current->y, current->x);
    active_user->under_ch = next_ch;
    attron(COLOR_PAIR(active_user->player_color));
    mvaddch(current->y, current->x, '@');
    attroff(COLOR_PAIR(active_user->player_color));
    refresh();
    int previos;
    int move = 0;
    // halfdelay(5);
    while(1) {
        g.hunger += active_user->difficulty + 1;
        if(g.hunger >= 100)
            return 1;
        int index = is_in_room(*current);
        if(index >= 0)
        {
            floors_arr[active_floor].rooms_arr[index].visible = 1;
            rooms_arr[active_floor][index].visible = 1;
        }
        print_floor();
        attron(COLOR_PAIR(active_user->player_color));
        mvaddch(current->y, current->x, '@');
        attroff(COLOR_PAIR(active_user->player_color));
        if(index < -1 && (previos & A_CHARTEXT) == '#') {
            message("You Entered a room (press any KEY to continue!)", COLOR_PAIR(12) | A_BLINK | A_BOLD);
            // cbreak();
            getch();
            // halfdelay(5);
        }
        previos = active_user->under_ch;
        // active_user->under_ch = next_ch;
        if((active_user->under_ch & A_CHARTEXT) == '<') {
            message("You are on stairs use '<' to go to next floor", COLOR_PAIR(12));
        }
        else if((active_user->under_ch & A_CHARTEXT) == '>') {
            message("You are on stairs use '>' to go to previos floor", COLOR_PAIR(12));
        }
        refresh();
        int ch = getch();
        if(ch == ',' || ch == '<') {
            if((active_user->under_ch & A_CHARTEXT) == '<') {
            active_floor++;
            active_user->under_ch = ('>' | A_BOLD);
            print_floor();
            }
        }
        if(ch == '.' || ch == '>') {
            if((active_user->under_ch & A_CHARTEXT) == '>') {
            active_floor--;
            active_user->under_ch = ('<' | A_BOLD);
            }
        }
        if(ch == 'w' || ch == 'W') { /*move up*/
            int next_ch = mvinch(current->y - 1, current->x);

            if((next_ch & A_CHARTEXT) != (ACS_ULCORNER & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_URCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_LLCORNER & A_CHARTEXT) &&  (next_ch & A_CHARTEXT) != (ACS_LRCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_HLINE & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_VLINE & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != ' ')
            {
                mvaddch(current->y, current->x, active_user->under_ch);
                current->y--;
                attron(COLOR_PAIR(active_user->player_color));
                mvaddch(current->y, current->x, '@');
                attroff(COLOR_PAIR(active_user->player_color));
                active_user->under_ch = next_ch;          
                      
            }
        }
        else if(ch == 'a' || ch == 'A') { /*move left*/
            int next_ch = mvinch(current->y, current->x - 1);

            if((next_ch & A_CHARTEXT) != (ACS_ULCORNER & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_URCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_LLCORNER & A_CHARTEXT) &&  (next_ch & A_CHARTEXT) != (ACS_LRCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_HLINE & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_VLINE & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != ' ')
            {
                mvaddch(current->y, current->x, active_user->under_ch);
                current->x--;
                attron(COLOR_PAIR(active_user->player_color));
                mvaddch(current->y, current->x, '@');
                attroff(COLOR_PAIR(active_user->player_color));
                active_user->under_ch = next_ch;                
            }
        }
        else if(ch == 's' || ch == 'S') { /*move down*/
            int next_ch = mvinch(current->y + 1, current->x);

            if((next_ch & A_CHARTEXT) != (ACS_ULCORNER & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_URCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_LLCORNER & A_CHARTEXT) &&  (next_ch & A_CHARTEXT) != (ACS_LRCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_HLINE & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_VLINE & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != ' ')
            {
                mvaddch(current->y, current->x, active_user->under_ch);
                current->y++;
                attron(COLOR_PAIR(active_user->player_color));
                mvaddch(current->y, current->x, '@');
                attroff(COLOR_PAIR(active_user->player_color));
                active_user->under_ch = next_ch;                
            }
        }
        else if(ch == 'd' || ch == 'D') { /*move right*/
            int next_ch = mvinch(current->y, current->x + 1);

            if((next_ch & A_CHARTEXT) != (ACS_ULCORNER & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_URCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_LLCORNER & A_CHARTEXT) &&  (next_ch & A_CHARTEXT) != (ACS_LRCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_HLINE & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_VLINE & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != ' ')
            {
                mvaddch(current->y, current->x, active_user->under_ch);
                current->x++;
                attron(COLOR_PAIR(active_user->player_color));
                mvaddch(current->y, current->x, '@');
                attroff(COLOR_PAIR(active_user->player_color));
                active_user->under_ch = next_ch;                
            }
        }
        
        else if(ch == 'q' || ch == 'Q') { /*move up-left*/
            int next_ch = mvinch(current->y - 1, current->x - 1);

            if((next_ch & A_CHARTEXT) != (ACS_ULCORNER & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_URCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_LLCORNER & A_CHARTEXT) &&  (next_ch & A_CHARTEXT) != (ACS_LRCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_HLINE & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_VLINE & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != ' ')
            {
                mvaddch(current->y, current->x, active_user->under_ch);
                current->x--;
                current->y--;
                attron(COLOR_PAIR(active_user->player_color));
                mvaddch(current->y, current->x, '@');
                attroff(COLOR_PAIR(active_user->player_color));
                active_user->under_ch = next_ch;                
            }
        }
        else if(ch == 'e' || ch == 'E') { /*move up-right*/
            int next_ch = mvinch(current->y - 1, current->x + 1);

            if((next_ch & A_CHARTEXT) != (ACS_ULCORNER & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_URCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_LLCORNER & A_CHARTEXT) &&  (next_ch & A_CHARTEXT) != (ACS_LRCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_HLINE & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_VLINE & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != ' ')
            {
                mvaddch(current->y, current->x, active_user->under_ch);
                current->x++;
                current->y--;
                attron(COLOR_PAIR(active_user->player_color));
                mvaddch(current->y, current->x, '@');
                attroff(COLOR_PAIR(active_user->player_color));
                active_user->under_ch = next_ch;                
            }
        }
        else if(ch == 'z' || ch == 'Z') { /*move down-left*/
            int next_ch = mvinch(current->y + 1, current->x - 1);

            if((next_ch & A_CHARTEXT) != (ACS_ULCORNER & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_URCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_LLCORNER & A_CHARTEXT) &&  (next_ch & A_CHARTEXT) != (ACS_LRCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_HLINE & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_VLINE & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != ' ')
            {
                mvaddch(current->y, current->x, active_user->under_ch);
                current->x--;
                current->y++;
                attron(COLOR_PAIR(active_user->player_color));
                mvaddch(current->y, current->x, '@');
                attroff(COLOR_PAIR(active_user->player_color));
                active_user->under_ch = next_ch;                
            }
        }
        else if(ch == 'x' || ch == 'X') { /*move down-right*/
            int next_ch = mvinch(current->y + 1, current->x + 1);

            if((next_ch & A_CHARTEXT) != (ACS_ULCORNER & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_URCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_LLCORNER & A_CHARTEXT) &&  (next_ch & A_CHARTEXT) != (ACS_LRCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_HLINE & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_VLINE & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != ' ')
            {
                mvaddch(current->y, current->x, active_user->under_ch);
                current->x++;
                current->y++;
                attron(COLOR_PAIR(active_user->player_color));
                mvaddch(current->y, current->x, '@');
                attroff(COLOR_PAIR(active_user->player_color));
                active_user->under_ch = next_ch;                
            }
        }

        /*Fast moves*/
        else if(ch == KEY_LEFT) {
            int next_ch = mvinch(current->y, current->x - 1);

            while((next_ch & A_CHARTEXT) != (ACS_ULCORNER & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_URCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_LLCORNER & A_CHARTEXT) &&  (next_ch & A_CHARTEXT) != (ACS_LRCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_HLINE & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_VLINE & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != ' ')
            {   

                mvaddch(current->y, current->x, active_user->under_ch);
                current->x--;
                current->y;
                attron(COLOR_PAIR(active_user->player_color));
                mvaddch(current->y, current->x, '@');
                attroff(COLOR_PAIR(active_user->player_color));
                active_user->under_ch = next_ch;
                next_ch = mvinch(current->y, current->x - 1);
                index = is_in_room(*current);
                if(index >= 0)
                    floors_arr[active_floor].rooms_arr[index].visible = 1;                
                print_floor();              
            }
        }
        else if(ch == KEY_UP) {
            int next_ch = mvinch(current->y - 1, current->x);

            while((next_ch & A_CHARTEXT) != (ACS_ULCORNER & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_URCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_LLCORNER & A_CHARTEXT) &&  (next_ch & A_CHARTEXT) != (ACS_LRCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_HLINE & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_VLINE & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != ' ')
            {   

                mvaddch(current->y, current->x, active_user->under_ch);
                current->x;
                current->y--;
                attron(COLOR_PAIR(active_user->player_color));
                mvaddch(current->y, current->x, '@');
                attroff(COLOR_PAIR(active_user->player_color));
                active_user->under_ch = next_ch;
                next_ch = mvinch(current->y - 1, current->x);
                index = is_in_room(*current);
                if(index >= 0)
                    floors_arr[active_floor].rooms_arr[index].visible = 1;                
                print_floor();              
            }
        }
        else if(ch == KEY_DOWN) {
            int next_ch = mvinch(current->y + 1, current->x);

            while((next_ch & A_CHARTEXT) != (ACS_ULCORNER & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_URCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_LLCORNER & A_CHARTEXT) &&  (next_ch & A_CHARTEXT) != (ACS_LRCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_HLINE & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_VLINE & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != ' ')
            {   

                mvaddch(current->y, current->x, active_user->under_ch);
                current->x;
                current->y++;
                attron(COLOR_PAIR(active_user->player_color));
                mvaddch(current->y, current->x, '@');
                attroff(COLOR_PAIR(active_user->player_color));
                active_user->under_ch = next_ch;
                next_ch = mvinch(current->y + 1, current->x);
                index = is_in_room(*current);
                if(index >= 0)
                    floors_arr[active_floor].rooms_arr[index].visible = 1;                
                print_floor();              
            }
        }
        else if(ch == KEY_RIGHT) {
            int next_ch = mvinch(current->y, current->x + 1);

            while((next_ch & A_CHARTEXT) != (ACS_ULCORNER & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_URCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_LLCORNER & A_CHARTEXT) &&  (next_ch & A_CHARTEXT) != (ACS_LRCORNER & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != (ACS_HLINE & A_CHARTEXT) && (next_ch & A_CHARTEXT) != (ACS_VLINE & A_CHARTEXT) &&
            (next_ch & A_CHARTEXT) != ' ')
            {   

                mvaddch(current->y, current->x, active_user->under_ch);
                current->x++;
                current->y;
                attron(COLOR_PAIR(active_user->player_color));
                mvaddch(current->y, current->x, '@');
                attroff(COLOR_PAIR(active_user->player_color));
                active_user->under_ch = next_ch;
                next_ch = mvinch(current->y, current->x + 1);  
                index = is_in_room(*current);
                if(index >= 0)
                    floors_arr[active_floor].rooms_arr[index].visible = 1;
                print_floor();              
            }
        }
        
        else if(ch == 'm' || ch == 'M') {
            if(!is_visible)
                is_visible = 1;
            else
                is_visible = 0;
        }


        else if(ch == 27) {
            active_user->active_floor = active_floor;
            clear();
            attron(COLOR_PAIR(3) | A_BOLD);
            mvprintw(LINES / 2, (COLS - 15) / 2, "Saving Game...");
            attroff(COLOR_PAIR(3) | A_BOLD);
            refresh();
            usleep(100000);
            save_users(&arr, users_count);
            // cbreak();
            return 27;
        }
        
        refresh();
    }
    // cbreak();
}

int resume_game() {
    g = active_user->last_game;
    if(active_user->floors_arr[0].rooms_count == 0)
    {
        return 404;
    }
    print_floor();
    add_tools();
    add_golds();
    add_foods();
    clear();
    print_floor();
    refresh();
    int val = player_movement();
    if (val == 1)

    if(val == 27)
        active_user->last_game = g;
}

int is_in_room(Pos p) {
    for(int i = 0; i < rooms_count[active_floor]; i++) {
        Room temp = rooms_arr[active_floor][i];
        // if(p.x >= temp.x && p.x  <= temp.x + temp.width && p.y >= temp.y && p.y <= temp.y + temp.height)
        //     return -i - 1;
        for(int j = 0; j < temp.door_num; j++ ) {
            if(abs(p.x - (temp.x + temp.doors[j].x)) == 0 && abs(p.y - (temp.y + temp.doors[j].y)) == 0)
                return -i - 2;
            if(abs(p.x - (temp.x + temp.doors[j].x)) <= 2 && abs(p.y - (temp.y + temp.doors[j].y)) <= 2)
                return i;
        }
    }
    return -1;
}
