//
// Created by Ben on 12/12/2018.
//

#include "rooms_functions.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
//#define DEBUG //Define DEBUG to see lots of debugging output

// Function to read Rooms from the user specified directory and store the amount of practical and lecture rooms
void read_rooms_file(char *temp_directory, Room rooms[]){
    char directory[101];
    strcpy(directory, temp_directory);
    strcat(directory, ROOM_FILE);

    FILE* rooms_file = fopen(directory, "r");


    //Reading the file line by line and storing the type and number of rooms
    //***NOTE - this would need to be updated if any extra room types were added ***
    //this could be done by adding extra switch cases

    for(int i=0; i<NUM_ROOM_TYPES; i++) {
        (fscanf(rooms_file, "%c %i ", &rooms[i].room_type, &rooms[i].num_of_rooms));

        //All this does is coverts the char to a more user friendly output and stores it in the current room structure
        switch (rooms[i].room_type) {
            case 'L':
#ifdef DEBUG
                printf("Found a room of type %c, storing this as a Lecture. \n", rooms[i].room_type);
#endif
                strcpy(rooms[i].room_name, "Lecture");
                break;
            case 'P':
#ifdef DEBUG
                printf("Found a room of type %c, storing this as a Practical. \n", rooms[i].room_type);
#endif
                strcpy(rooms[i].room_name, "Practical");
                break;
            default:
                printf("Found a room of type %c, this room type was not recognized - consider adding it to the read_rooms_file "
                       "function.\n", rooms[i].room_type);
                strcpy(rooms[i].room_name, "Invalid room");
                break;
        }
    }

    fclose(rooms_file);
    printf("Room file complete.\n");
    //Now print out in a user friendly format
    //***NOTE - this would need to be updated if any extra room types were added ***
    int totalRooms =0;
    for(int i=0; i<NUM_ROOM_TYPES; i++){
        printf("The number of %s(%c) rooms available is: %d.\n",
          rooms[i].room_name,rooms[i].room_type, rooms[i].num_of_rooms);
        totalRooms += rooms[i].num_of_rooms;
    }

    //printing total rooms available
    printf("The total number of rooms available is %d.\n",totalRooms);
}

