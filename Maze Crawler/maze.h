#ifndef MAZE_H
#define	MAZE_H
/* 
 * File:   maze.h
 * Authors: Ben Weatherley
 * 
 * A header file that contains macros and structures my other file(s) will use
 */

#ifdef	__cplusplus
extern "C" {
#endif


/*Setting the number of rooms on the X and Y axis of the maze*/
#define MAZE_ROOM_X 5
#define MAZE_ROOM_Y 5
#define STARTING_ROOM_X 1
#define STARTING_ROOM_Y 0
#define WALL_IR_VALUE 100 //the cutoff point for deciding if a wall exists

/*Direction the robot is facing is tracked with ints, defining the values for 
 readability*/
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
    
   
/*A structure to represent "rooms" in the maze */
typedef struct room{
    bool north_wall;
    bool east_wall;
    bool south_wall;
    bool west_wall;
    bool visited;
    bool nest;
    int breadcrumb;
}Room;
     

/*Function declarations*/
/*function to update the current room of the maze*/
void update_current_room();
/*function to setup the initial values for each room in the maze*/
void setup_maze();
/*------------------------------------------------------------------------------
 Reactive behaviours*/
void explore(void);
void read_line(void);
/*------------------------------------------------------------------------------
Inspecting room functions*/
void inspect_room(void);
void inspect_nest();
void inspect_walls(void);
void inspect_walls_north(void);
void inspect_walls_east(void);
void inspect_walls_south(void);
void inspect_walls_west(void);
bool check_nest(void);
/*------------------------------------------------------------------------------
Decide direction functions*/
void decide_direction(void);
void decide_direction_north(void);
void decide_direction_east(void);
void decide_direction_south(void);
void decide_direction_west(void);

/*------------------------------------------------------------------------------
 Get average reading functions*/
int get_ldr_reading(void);
int get_lineir_reading(void);
int get_left_lineir_reading(void);
int get_right_lineir_reading(void);
int get_leftir_reading(void);
int get_frontir_reading(void);
int get_rightir_reading(void);
int get_rearir_reading(void);
/*------------------------------------------------------------------------------
 functions to handle returning to the nest*/
void nest_decide_direction();
int nest_check_north(int x_room, int y_room);
int nest_check_east(int x_room, int y_room);
int nest_check_south(int x_room, int y_room);
int nest_check_west(int x_room, int y_room);
void nest_turn(int best_room);
void nest_turn_north();
void nest_turn_east();
void nest_turn_south();
void nest_turn_west();


#ifdef	__cplusplus
}
#endif

#endif	/* MAZE_H */

