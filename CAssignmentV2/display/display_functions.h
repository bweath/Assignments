//
// Created by Ben on 12/12/2018.
//

#ifndef CASSIGNMENTV2_DISPLAY_FUNCTIONS_H
#define CASSIGNMENTV2_DISPLAY_FUNCTIONS_H

#include "../common.h"
//prints information about a user input module
void print_module_information(Scheme *schemes,char module_name[MODULE_CODE_LENGTH], int num_of_schemes);

//prints the timetable
void print_timetable(Day days[DAYS_IN_WEEK]);

//prints out the column titles for our table
void print_columns();

//Takes an int and prints out the corresponding day in the format of our table
void print_day(int day);
#endif //CASSIGNMENTV2_DISPLAY_FUNCTIONS_H
