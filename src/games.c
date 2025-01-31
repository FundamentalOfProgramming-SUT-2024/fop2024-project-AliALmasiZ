#include "games.h"
#define DEBUG
Room rooms_arr[MAX_FLOORS][MAX_ROOMS] = {0};
int rooms_count[MAX_FLOORS] = {0};
int active_floor = 0;

Pos visited[MAX_PATH] = {};
int visited_count = 0;

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
    if(can_make(rooms_arr[active_floor][rooms_count[active_floor]])) {
        rooms_arr[active_floor][rooms_count[active_floor]].door_num = rand() % 3 + 1;
        for(int i = 0; i < rooms_arr[active_floor][rooms_count[active_floor]].door_num; i++) {
            rooms_arr[active_floor][rooms_count[active_floor]].door_wall[i] = rand() % 4;
            switch (rooms_arr[active_floor][rooms_count[active_floor]].door_wall[i]) {
            case 0:
                rooms_arr[active_floor][rooms_count[active_floor]].doors[i][0] = rand() % (width - 1) + 1;
                rooms_arr[active_floor][rooms_count[active_floor]].doors[i][1] = 0;
                break;
            
            case 1:
                rooms_arr[active_floor][rooms_count[active_floor]].doors[i][0] = width;
                rooms_arr[active_floor][rooms_count[active_floor]].doors[i][1] = rand() % (height - 1) + 1;
                break;

            case 2:
                rooms_arr[active_floor][rooms_count[active_floor]].doors[i][0] = rand() % (width - 1) + 1;
                rooms_arr[active_floor][rooms_count[active_floor]].doors[i][1] = height;
                break;

            case 3: 
                rooms_arr[active_floor][rooms_count[active_floor]].doors[i][0] = 0;
                rooms_arr[active_floor][rooms_count[active_floor]].doors[i][1] = rand() % (height - 1) + 1;
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
int compare_door_dis(const void *a, const void *b) {
    
}
void print_rooms() {
    // qsort(rooms_arr[active_floor], MAX_ROOMS, sizeof(Room), compare_distance);
    attron(A_BOLD);
    for(int i = 0; i < rooms_count[active_floor]; i++) {
        Room temp = rooms_arr[active_floor][i];
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
        for(int j = 0; j < temp.door_num; j++) {
            mvaddch(temp.y + temp.doors[j][1], temp.x + temp.doors[j][0], '+');
        }
    }
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
/*void draw_hallway1(int start_x, int start_y, int end_x, int end_y) {
    int x, y;
    if(end_y < start_y) {
        int temp = end_y;
        end_y = start_y;
        start_y = temp;
    }
    x = start_x;
    y = start_y;
    int left, right, up, down;
    while (1){    
        left = is_overlap(x - 1, y) + is_visited(visited, visited_count, x - 1, y);
        right = is_overlap(x + 1, y) + is_visited(visited, visited_count, x + 1, y);
        up = is_overlap(x, y - 1) + is_visited(visited, visited_count, x, y - 1);
        down = is_overlap(x, y + 1) + is_visited(visited, visited_count, x, y + 1);
        if(left == 2 || right == 2 || up == 2 || down == 2) {
            if(x - end_x <= 1 && end_x - x <= 1 && y - end_y <= 1 && end_y - y <= 1)
                break;
        }
        if(x > end_x) {
            if(!left) {
                x--;
            }
            else if(y > end_y) {
                if(!up) 
                    y--;
                else if (!down) 
                    y++;
                else if(!right)
                    x++;
                else
                    exit(100);
            }
            else if(y <= end_y) {
                if(!down) 
                    y++;
                else if(!right)
                    x++;
                else if (!up) 
                    y--;
                else
                    exit(100);
            }
            else    
                exit(100);
        }
        else if(x < end_x) {
            if(!right) {
                x++;
            }
            else if(y > end_y) {
                if(!up) 
                    y--;
                else if (!down) 
                    y++;
                else if(!left)
                    x--;
                else
                    exit(100);
            }
            else if(y <= end_y) {
                if(!down) 
                    y++;
                else if(!left)
                    x--;
                else if (!up) 
                    y--;
                else
                    exit(100);
            }
            else    
                exit(100);
        }
        else if (x == end_x) 
        {
            if(y == end_y)
                break;
            else if(y > end_y) {
                if(!up) 
                    y--;
                else if(!left)
                    x--;
                else if(!right)
                    x++;
                else if (!down) 
                    y++;
                else
                    exit(100);
            }
            else if(y < end_y) {
                if(!down) 
                    y++;
                else if(!left)
                    x--;
                else if(!right)
                    x++;
                else if (!up) 
                    y--;
                else
                    exit(100);
            }
            else    
                exit(100);
        }else 
            exit(100);
        // printf("(%d, %d), (%d, %d)\n", y, x, LINES, COLS);
        mvprintw(y, x, "#");
        visited[visited_count].x = x;
        visited[visited_count].y = y;
        visited_count++;
        refresh();
        usleep(100000);
    }

}*/
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
        /*Pos moves[4];
        if (dy != 0) {
            moves[0] = (Pos){current.x + 1, current.y};
            moves[1] = (Pos){current.x - 1, current.y};
            moves[2] = (Pos){current.x, current.y + 1};
            moves[3] = (Pos){current.x, current.y - 1};
        }
        else if (dx != 0) {
            moves[0] = (Pos){current.x, current.y + 1};
            moves[1] = (Pos){current.x, current.y - 1};
            moves[2] = (Pos){current.x - 1, current.y};
            moves[3] = (Pos){current.x + 1, current.y};
        }*/
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
                flag = 1;
            }
            else {
                moves[0] = (Pos){current.x + 1, current.y};
                moves[1] = (Pos){current.x - 1, current.y};
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
void draw_hallway() {
    for(int i = 1; i < visited_count; i++) {
        mvaddch(visited[i].y, visited[i].x, '#');
    }
}
void connect_doors() {

    qsort(rooms_arr[active_floor], rooms_count[active_floor], sizeof(Room), compare_distance);
    for (int i = 0; i < rooms_count[active_floor] - 1; i++) {
        Room room1 = rooms_arr[active_floor][i];
        Room room2 = rooms_arr[active_floor][i + 1];
        int door1_x = room1.x + room1.doors[0][0];
        int door1_y = room1.y + room1.doors[0][1];
        int door2_x = room2.x + room2.doors[0][0];
        int door2_y = room2.y + room2.doors[0][1];
        visited_count = 0;
        make_hallway(door1_x, door1_y, door2_x, door2_y);
        // draw_hallway();
    }
}
void generate_floor() {
    int counter = 0;
    rooms_count[active_floor] = 0;
    while(rooms_count[active_floor] < 6 || counter < 20) {
        counter++;
        generate_room();
    }
    print_rooms();
    connect_doors();
    refresh();
    getch();
    
}
void print_floor() {
    

}