//
// Created by Ben on 12/12/2018.
//

#ifndef CASSIGNMENTV2_FUNCTIONS_H
#define CASSIGNMENTV2_FUNCTIONS_H

#include "../../common.h"
// Reads in modules from a file
void read_module_file(char *temp_directory, Module **modules);

// Creates a module to be stored in a linked list
Module* create_module(char mc[MODULE_CODE_LENGTH], int semester, char lect_info[4], char pract_info[4]);

#endif //CASSIGNMENTV2_FUNCTIONS_H
