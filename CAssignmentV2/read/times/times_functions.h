//
// Created by Ben on 12/12/2018.
//

#ifndef CASSIGNMENTV2_TIMES_FUNCTIONS_H
#define CASSIGNMENTV2_TIMES_FUNCTIONS_H
#include "../../common.h"

// Reads the available times from the times file
void read_times_file(char *temp_directory, Day days[]);

//takes an int and returns the appropriate index of the days array for that hour
int read_hour(int temp_hour);
#endif //CASSIGNMENTV2_TIMES_FUNCTIONS_H
