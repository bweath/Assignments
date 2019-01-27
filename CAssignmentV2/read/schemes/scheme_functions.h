//
// Created by Ben on 12/12/2018.
//

#ifndef CASSIGNMENTV2_SCHEME_FUNCTIONS_H
#define CASSIGNMENTV2_SCHEME_FUNCTIONS_H
#include "../../common.h"

// Reads in schemes from a file
void read_schemes_file(char *directory, Module *list, Scheme schemes[], int num_of_schemes);

// Used to add modules to a schemes
void add_modules(char module_code[MODULE_CODE_LENGTH],Module *list, Module **head);


#endif //CASSIGNMENTV2_SCHEME_FUNCTIONS_H
