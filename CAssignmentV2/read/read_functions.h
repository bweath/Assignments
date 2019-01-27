//
// Created by Ben on 12/12/2018.
//

#ifndef CASSIGNMENTV2_READ_FUNCTIONS_H
#define CASSIGNMENTV2_READ_FUNCTIONS_H

#include "../common.h"
#include "modules/module_functions.h"
#include "schemes/scheme_functions.h"
#include "rooms/rooms_functions.h"
#include "times/times_functions.h"


//Takes all of our structures as parameters and calls the relevant read functions to fill them
void read_all_files(char directory_path[], Module **modules, Scheme schemes[], int number_of_schemes,Room rooms[], Day days[]);

// Used to count lines in a file
int count_lines(char *directory);
#endif //CASSIGNMENTV2_READ_FUNCTIONS_H
