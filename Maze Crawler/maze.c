#include "allcode_api.h"
#include "maze.h"
/* 
 * File:   maze.c
 * Authors: Ben Weatherley
 * 
 * A program to navigate and store information of a maze
 */


   static Room maze[MAZE_ROOM_X][MAZE_ROOM_Y]; /*creating the maze*/
   static int found_rooms = 0;
   /*integer to keep track of where the robot is facing*/
   static int robot_direction = NORTH;
   /*integers to keep track of where we are in the maze*/
   static int current_room_x = STARTING_ROOM_X; 
   static int current_room_y = STARTING_ROOM_Y;
int main()
{
	FA_RobotInit();
    FA_ResetEncoders();
    FA_SetDriveSpeed(40);

  
    setup_maze(); /*loops through all rooms in the maze and sets their values*/
    while(FA_ReadSwitch(0) == 0){
             
         }
    FA_DelaySecs(1);
    /* loop until we have explored the entire maze*/
     while(found_rooms < (MAZE_ROOM_X * MAZE_ROOM_Y)){ 
         
         if(!maze[current_room_x][current_room_y].visited){
             inspect_room();
         }
         inspect_nest(); 
         /*We dont want to decide a direction and move to the next room if we
          just inspected the final room of the maze*/
         if(found_rooms < (MAZE_ROOM_X * MAZE_ROOM_Y) ){ 
         decide_direction();
         explore();
         update_current_room();
         }   
     }
      /*loop here until we arrive back at the nest*/
    FA_PlayNote(600, 100);//play a note to show maze is explored
    /* think I need to be careful about the current location becoming 1 room
     out of sync when the maze is explored*/
    while(!maze[current_room_x][current_room_y].nest){
        nest_decide_direction();
        explore();
        update_current_room();
     
    }
    FA_PlayNote(600, 200);
    FA_DelayMicros(300);
    FA_PlayNote(400, 200);
    FA_DelayMicros(300);
    FA_PlayNote(200, 200);
 	return 0;
}

/*----------------------------------------------------------------------------
 Function to update the robots current room in the maze*/

void update_current_room(){
   
     switch (robot_direction){
        case NORTH: /* robot facing north, so moved 1 room up */
            current_room_y += 1;
            break;
        case EAST: /*robot facing east, so moved 1 room across to the east*/
            current_room_x += 1;
            break;
        case SOUTH: /*robot facing south, so moved 1 room down*/
            current_room_y -= 1; 
            break;
        case WEST: /*robot facing west, so moved 1 room across to the west*/
            current_room_x -= 1;
            break;
     }
}

/*Function to setup the values for every room in the maze (only ever called once
 or we would overwrite all our information)*/
void setup_maze(){
    int x;
    int y;  
    for (x = 0; x < MAZE_ROOM_X; x++){
        for (y = 0; y < MAZE_ROOM_Y; y++){
            maze[x][y].north_wall = true;
            maze[x][y].east_wall = true;
            maze[x][y].south_wall = true;
            maze[x][y].west_wall = true;
            maze[x][y].breadcrumb = 101;
            maze[x][y].nest = false;
            maze[x][y].visited = false;
        }
    }
}

/*-----------------------------------------------------------------------------
Functions to do with reactive behaviour*/

void explore(){
    while(get_lineir_reading() > 100){
        int state = 0;
        /*not gonna use averages here as it would slow the process down a lot*/
        
        /*if the front IR is above the threshold reverse*/
        if (FA_ReadIR(2) > 900) {state = 3;}
        /*commenting all this out to try and fix a problem im having
         where wheels stop spinning*/
        /*if front left IR is above the threshold turn to the right
        else if (FA_ReadIR(1) > 800) {state = 2;}
        if front right IR is above the threshold turn the the left
        else if (FA_ReadIR(3) > 800) {state = 1;}
        otherwise drive straight(ish)*/
        else {state = 0;}
        /*may want some other states using the left and right IR readers*/
        
        
        switch (state){
        case 0: /*go forwards*/
            FA_SetMotors(40,40);
            break;
        case 1: /*avoid left*/
            FA_SetMotors(20,21); /*not used at the moment*/
            break;
        case 2: /*avoid right*/
            FA_SetMotors(21,20); /*not used at the moment*/
            break;
        case 3: /*reverse*/
            FA_Backwards(50);
            break;
        }
    } 
read_line();    
}


void read_line(){ 
    int left, right, difference;
    left = get_left_lineir_reading();
    right = get_right_lineir_reading();
    difference = left - right;
    if (difference > 100){ /*robot is angled right*/
        FA_Backwards(40);
        FA_Right(5);
        explore();
    } else if (difference < -100){ /*robot is angled left*/
        FA_Backwards(40);
        FA_Left(5);
        explore();
    } else{
        FA_Forwards(115);
    }
}

/*----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 All functions specifically to do with the "inspect room" state
 */


/*
 function for inspecting a room
 Whenever the robot enters a new room this function will be called to inspect it
 */
void inspect_room(){
   
    found_rooms += 1; /*keep track of unique rooms found so we know when to stop*/ 
    maze[current_room_x][current_room_y].visited = true;
    inspect_walls(); /*collects data about this rooms walls*/
}

/*function for checking for the nest and dropping breadcrumbs*/
void inspect_nest(){
    static bool found_nest = false;
    if (!found_nest){
        found_nest = check_nest();
    } else{ 
        /*set the current rooms breadcrumb value then increment breadcrumb*/
        static int breadcrumb =1;
        maze[current_room_x][current_room_y].breadcrumb = breadcrumb;
        breadcrumb++;
    }
}

void inspect_walls(){
    switch (robot_direction){
        case NORTH: /* robot facing north */
            inspect_walls_north();
            break;
        case EAST: /*robot facing east*/
            inspect_walls_east();
            break;
        case SOUTH: /*robot facing south*/
            inspect_walls_south();
            break;
        case WEST: /*robot facing west*/
            inspect_walls_west();
            break;
    }
}

/*
 Inspects the walls when the robot is facing north
 */
void inspect_walls_north(){
    if (get_leftir_reading() < WALL_IR_VALUE) 
               maze[current_room_x][current_room_y].west_wall = false;
            
    if (get_frontir_reading() < WALL_IR_VALUE) 
                maze[current_room_x][current_room_y].north_wall = false;
            
    if (get_rightir_reading() < WALL_IR_VALUE) 
                maze[current_room_x][current_room_y].east_wall = false;
            
    if (get_rearir_reading() < WALL_IR_VALUE) 
                maze[current_room_x][current_room_y].south_wall = false;
}

/*
 Inspects the walls when the robot is facing east
 */
void inspect_walls_east(){
    if (get_leftir_reading() < WALL_IR_VALUE) 
                maze[current_room_x][current_room_y].north_wall = false;
            
    if (get_frontir_reading() < WALL_IR_VALUE) 
                maze[current_room_x][current_room_y].east_wall = false;
            
    if (get_rightir_reading() < WALL_IR_VALUE) 
                maze[current_room_x][current_room_y].south_wall = false;
            
    if (get_rearir_reading() < WALL_IR_VALUE) 
                maze[current_room_x][current_room_y].west_wall = false;
}

/*
 Inspects the walls when the robot is facing south
 */
void inspect_walls_south(){
    if (get_leftir_reading() < WALL_IR_VALUE) 
                maze[current_room_x][current_room_y].east_wall = false;
            
    if (get_frontir_reading() < WALL_IR_VALUE) 
                maze[current_room_x][current_room_y].south_wall = false;
            
    if (get_rightir_reading() < WALL_IR_VALUE) 
                maze[current_room_x][current_room_y].west_wall = false;
            
    if (get_rearir_reading() < WALL_IR_VALUE) 
                maze[current_room_x][current_room_y].north_wall = false;
}


/*
 Inspects the walls when the robot is facing west
 */
void inspect_walls_west(){
    if (get_leftir_reading() < WALL_IR_VALUE) 
                maze[current_room_x][current_room_y].south_wall = false;
            
    if (get_frontir_reading() < WALL_IR_VALUE) 
                maze[current_room_x][current_room_y].west_wall = false;
            
    if (get_rightir_reading() < WALL_IR_VALUE) 
                maze[current_room_x][current_room_y].north_wall = false;
            
    if (get_rearir_reading() < WALL_IR_VALUE) 
                maze[current_room_x][current_room_y].east_wall = false;
}


/*
 Checks if the room is dark, if it is, then this room becomes the nest
 */
bool check_nest(){ 
    if (get_ldr_reading() < 200){
        /*if we find the nest, set nest found to true*/
        maze[current_room_x][current_room_y].nest = true; 
        /*then drop the first breadcrumb*/
        maze[current_room_x][current_room_y].breadcrumb = 0;
        FA_PlayNote(600, 100); //play a note for debugging purposes
    }
    return maze[current_room_x][current_room_y].nest;
}
/*----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
The following functions decide which direction the robot should turn and face*/
void decide_direction(){
    switch (robot_direction){
        case NORTH: /* robot facing north */
            decide_direction_north();
            break;
        case EAST: /*robot facing east*/
            decide_direction_east();
            break;
        case SOUTH: /*robot facing south*/
            decide_direction_south();
            break;
        case WEST: /*robot facing west*/
            decide_direction_west();
            break;
    }
}

/*Note:
         I understand that I am using alot of blocking functions for turning
         however the robot should not need to do any actions during these turns
         as it is just lining up ready for the next hybrid phase*/
void decide_direction_north(){
    if(!maze[current_room_x][current_room_y].west_wall){
        FA_Left(90);
        robot_direction = WEST;
    }
    else if(!maze[current_room_x][current_room_y].north_wall){
     /*Already facing the correct direction*/}
    else if(!maze[current_room_x][current_room_y].east_wall){
        FA_Right(90);
        robot_direction = EAST;
    }
    else{ 
        FA_Left(180); /*Dead end, need to go back*/
        robot_direction = SOUTH;
    }
}

void decide_direction_east(){
    if(!maze[current_room_x][current_room_y].north_wall) {
        FA_Left(90);
        robot_direction = NORTH;
    }
    else if(!maze[current_room_x][current_room_y].east_wall){
     /*Already facing the correct direction*/}
    else if(!maze[current_room_x][current_room_y].south_wall){
        FA_Right(90);
        robot_direction = SOUTH;
    }
    else {
     FA_Left(180); /*Dead end, need to go back*/
     robot_direction = WEST;
    }
}

void decide_direction_south(){
    if(!maze[current_room_x][current_room_y].east_wall) {
        FA_Left(90);
        robot_direction = EAST;
    }
    else if(!maze[current_room_x][current_room_y].south_wall){
     /*Already facing the correct direction*/}
    else if(!maze[current_room_x][current_room_y].west_wall){
        FA_Right(90);
        robot_direction = WEST;
    }
    else {
        FA_Left(180); /*Dead end, need to go back*/
        robot_direction = NORTH;
    }
}

void decide_direction_west(){
    if(!maze[current_room_x][current_room_y].south_wall){
        FA_Left(90);
        robot_direction = SOUTH;
    }
    else if(!maze[current_room_x][current_room_y].west_wall){
     /*Already facing the correct direction*/}
    else if(!maze[current_room_x][current_room_y].north_wall){
        FA_Right(90);
        robot_direction = NORTH;
    }
    else {
        FA_Left(180); /*Dead end, need to go back*/
        robot_direction = EAST;
    }
}

/*----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Functions to do with taking average readings*/

/*
 Takes the average of 50 readings from the LDR
 This IS a blocking function, but it takes so little time it should not matter
 especially as this is called in the "decisive" part of the robot 
 */
int get_ldr_reading(){
    long average_reading = 0;
    int i;
    for(i=0;i<50;i++){
        average_reading += FA_ReadLight();
    }
    average_reading = average_reading/50;
    return average_reading;
}


/*
 Takes the average of 10 readings from the IR line readers and gets the average
 */

int get_lineir_reading(){
    long left = 0;
    long right = 0;
    int i;
    for(i=0;i<10;i++){
        left += FA_ReadLine(0); 
    }
    for(i=0;i<10;i++){
        right += FA_ReadLine(1); 
    }
    left = left/10;
    right = right/10;
    if(left > right){
        return right;
    } else{
        return left;
    }
}

int get_left_lineir_reading(){
    long average = 0;
    int i;
    for(i=0;i<10;i++){
        average += FA_ReadLine(0); 
    }
    average = average/10;
    return average;        
}

int get_right_lineir_reading(){
    long average = 0;
    int i;
    for(i=0;i<10;i++){
        average += FA_ReadLine(1); 
    }
    average = average/10;
    return average;  
    
}


/*
 Takes 50 readings from IR channel 0 (the left IR sensor)
 and returns the average
 */
int get_leftir_reading(){
    long average_reading = 0;
    int i;
    for(i=0;i<50;i++){
        average_reading += FA_ReadIR(0);
    }
    average_reading = average_reading /50;
    return average_reading;
}


/*
 Takes 50 readings from IR channel 2 (the front IR sensor)
 and returns the average
 */
int get_frontir_reading(){
    long average_reading = 0;
    int i;
    for(i=0;i<50;i++){
        average_reading += FA_ReadIR(2);
    }
    average_reading = average_reading /50;
    return average_reading;
}


/*
 Takes 50 readings from IR channel 4 (the right IR sensor)
 and returns the average
 */
int get_rightir_reading(){
    long average_reading = 0;
    int i;
    for(i=0;i<50;i++){
        average_reading += FA_ReadIR(4);
    }
    average_reading = average_reading /50;
    return average_reading;
}

/*
 Takes 50 readings from IR channel 6 (the rear IR sensor)
 and returns the average
 */
int get_rearir_reading(){
    long average_reading = 0;
    int i;
    for(i=0;i<50;i++){
        average_reading += FA_ReadIR(6);
    }
    average_reading = average_reading /50;
    return average_reading;
}


/*------------------------------------------------------------------------------
 Functions to do with getting back to the nest*/

void nest_decide_direction(){
    /*Need to examine the breadcrumb values of all adjacent rooms
     where there is an entrance*/
    int best_room; /*holds the direction of the best room*/
    int best_breadcrumb =100; /*holds the lowest breadcrumb value*/
    int temp_breadcrumb;
    int x_room = current_room_x;
    int y_room = current_room_y;
    
    temp_breadcrumb = nest_check_north(x_room, y_room);
    if (temp_breadcrumb < best_breadcrumb){
        best_breadcrumb = temp_breadcrumb;
        best_room = NORTH;
    }
    
    temp_breadcrumb = nest_check_east(x_room, y_room);
    if (temp_breadcrumb < best_breadcrumb){
        best_breadcrumb = temp_breadcrumb;
        best_room = EAST;
    }
    
    temp_breadcrumb = nest_check_south(x_room, y_room);
    if (temp_breadcrumb < best_breadcrumb){
        best_breadcrumb = temp_breadcrumb;
        best_room = SOUTH;
    }
    
    temp_breadcrumb = nest_check_west(x_room, y_room);
    if (temp_breadcrumb < best_breadcrumb){
        best_breadcrumb = temp_breadcrumb;
        best_room = WEST;
    }
    
    nest_turn(best_room); 
}

int nest_check_north(int x_room, int y_room){
    /*check if exit north*/
    if (!maze[x_room][y_room].north_wall){
        /*if exit, check if north is the best room*/
        y_room++;
        return maze[x_room][y_room].breadcrumb;
    }
    return 101; /*return large value to fail the < check*/
}

int nest_check_east(int x_room, int y_room){
    /*check if exit east*/
    if (!maze[x_room][y_room].east_wall){
        /*if exit, return breadcrumb value*/
        x_room++;
        return maze[x_room][y_room].breadcrumb;
    }
    return 101;
}

int nest_check_south(int x_room, int y_room){
    /*check if exit south*/
    if (!maze[x_room][y_room].south_wall){
        /*if exit, return breadcrumb value*/
        y_room--;
        return maze[x_room][y_room].breadcrumb;
    }
    return 101;
}

int nest_check_west(int x_room, int y_room){
    /*check if exit west*/
    if (!maze[x_room][y_room].west_wall){
        /*if exit, return breadcrumb value*/
        x_room--;
        return maze[x_room][y_room].breadcrumb;
    }
    return 101;
}


void nest_turn(int best_room){
    
      switch (best_room){
        case NORTH: /* Best room is north*/
            FA_LCDPrint("Best Room is North.", 20, 0,20,FONT_NORMAL, LCD_OPAQUE);
            nest_turn_north();
            break;
        case EAST: /* Best room is east*/
            FA_LCDPrint("Best Room is East.", 20, 0,20,FONT_NORMAL, LCD_OPAQUE);
            nest_turn_east();
            break;
        case SOUTH: /* Best room is south*/
            FA_LCDPrint("Best Room is South.", 20, 0,20,FONT_NORMAL, LCD_OPAQUE);
            nest_turn_south();
            break;
        case WEST: /* Best room is west*/
            FA_LCDPrint("Best Room is West.", 20, 0,20,FONT_NORMAL, LCD_OPAQUE);
            nest_turn_west();
            break;
     }
                
}


void nest_turn_north(){
    /*Turns the robot so it is facing north*/
    switch (robot_direction){
        case NORTH: 
            /*do nothing, robot facing correct direction*/
            break;
        case EAST: 
            FA_Left(90);
            break;
        case SOUTH:
            FA_Left(180);
            break;
        case WEST:
            FA_Right(90);
            break;
     }
    robot_direction = NORTH;
}

void nest_turn_east(){
    /*Turns the robot so it is facing east*/
    switch (robot_direction){
        case NORTH: 
            FA_Right(90);
            break;
        case EAST: 
             /*do nothing, robot facing correct direction*/
            break;
        case SOUTH:
            FA_Left(90);
            break;
        case WEST:
            FA_Left(180);
            break;
     }
    robot_direction = EAST;
}

void nest_turn_south(){
    /*Turns the robot so it is facing south*/
    switch (robot_direction){
        case NORTH: 
            FA_Left(180);
            break;
        case EAST: 
            FA_Right(90);
            break;
        case SOUTH:
            /*do nothing, robot facing correct direction*/
            break;
        case WEST:
            FA_Left(90);
            break;
     }
    robot_direction = SOUTH;
}

void nest_turn_west(){
    /*Turns the robot so it is facing west*/
    switch (robot_direction){
        case NORTH: 
            FA_Left(90);
            break;
        case EAST: 
            FA_Left(180);
            break;
        case SOUTH:
            FA_Right(90);
            break;
        case WEST:
            /*do nothing, robot facing correct direction*/
            break;
     }
    robot_direction = WEST;
}