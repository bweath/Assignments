//
// Created by Ben on 12/12/2018.
//

#include "times_functions.h"

#include "times_functions.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
//#define DEBUG
// Function to read times file from the user specified directory and store how many hours of teaching is available each day
void read_times_file(char *temp_directory, Day days[]){
    char directory[101];
    strcpy(directory, temp_directory);
    strcat(directory, TIME_FILE);

    FILE* times_file = fopen(directory, "r");

    char ignore[11]; //we don't care about the day value in the file so this will be ignored
    int num_hour_slots;


    for(int i=0; i<DAYS_IN_WEEK;i++){
        (fscanf(times_file, "%s %i ", ignore, &num_hour_slots));
#ifdef DEBUG
        printf("The day is %d.\n",i);
#endif
        for(int x=0; x<num_hour_slots;x++){
            int temp_hour;
            (fscanf(times_file, "%i",&temp_hour));
            //make available = 1 to the corresponding hour to signify its available
            days[i].hour[read_hour(temp_hour)].available =1;
#ifdef DEBUG
            printf("The hour is %d.\n",temp_hour);
#endif
        }
    }

    fclose(times_file);
}


// Function to take a time from the real world and covert it to our array representation 0=9am etc
int read_hour(int temp_hour) {
    switch (temp_hour) {
        case 9:
            return 0;
        case 10:
            return 1;
        case 11:
            return 2;
        case 12:
            return 3;
        case 13:
            return 4;
        case 14:
            return 5;
        case 15:
            return 6;
        case 16:
            return 7;
        case 17:
            return 8;
        default:
            printf("Unexpected or missing integer found in the times file, integer value was: %d.\n", temp_hour);
            return -1;
    };
}
