//
// Created by Ben on 12/12/2018.
//

#include "scheme_functions.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
//#define DEBUG

// Function to add schemes to an array
void read_schemes_file(char *temp_directory, Module *list, Scheme schemes[], int num_of_schemes) {

    char scheme_code[SCHEME_CODE_LENGTH];
    int year_of_study;
    int num_of_students;
    int num_of_modules;

    //making a copy of our directory, so that we can reuse the directory path for our other read file functions
    char directory[101];
    strcpy(directory, temp_directory);
    strcat(directory, SCHEME_FILE);

    FILE* schemes_file = fopen(directory, "r");

    for(int i=0; i<num_of_schemes;i++){
        fscanf(schemes_file, "%[^ ] %i %i %i ", scheme_code, &year_of_study, &num_of_students, &num_of_modules );

#ifdef DEBUG
        printf("Line %d \n",i);
           printf("%s %i %i %i \n", scheme_code, year_of_study, num_of_students, num_of_modules); //FOR DEBUGGING ONLY
#endif
        strcpy(schemes[i].scheme_code, scheme_code);
        schemes[i].year_of_study = year_of_study;
        schemes[i].num_of_students = num_of_students;
        schemes[i].num_of_modules = num_of_modules;
        schemes[i].head = NULL;
        //so far so good, now we need to loop for the number of modules, reading in modules from the file and adding them
        // to schemes[i]'s linked list
        for(int x=0;x<num_of_modules;x++){
            char module_code[MODULE_CODE_LENGTH];
            //If the module being read is'nt the last one, check for a space, otherwise check for an end of line carriage
            if (x<num_of_modules-1) {
                fscanf(schemes_file, "%[^ ] ", module_code);
            }else{
                fscanf(schemes_file, "%[^\n] ", module_code);
            }
#ifdef DEBUG
            printf("%s \n", module_code); //FOR DEBUGGING ONLY
#endif

            add_modules(module_code, list, &schemes[i].head);
        }
    }
    fclose(schemes_file);
    printf("Scheme file complete.\nThe number of schemes is: %d \n", num_of_schemes);
}


// Function that will add modules to schemas - will be called in read_schemes_file

void add_modules(char module_code[MODULE_CODE_LENGTH],Module *list, Module **head) {
//this function needs access to our linked list of moudules (list). It then needs to traverse this list until it finds
//the corresponding module. It then needs to COPY(as different schemes can have the same module) that module into the
//schemes linked list of modules.

//make a new pointer to the head of our modules file (so that we can reuse this pointer again and again)
    Module *temp_module = list;
    Module *next = NULL;
    next = *head;
    Module *new_module = malloc(sizeof(Module));

    while (temp_module != NULL) {
        if (strcmp(temp_module->module_code, module_code) == 0) {
            //creating a new module and copying info across to it (so that we don't lose the original copy)
            strcpy(new_module->module_code, temp_module->module_code);
            new_module->semester = temp_module->semester;
            new_module->num_of_lectures = temp_module->num_of_lectures;
            new_module->length_of_lectures = temp_module->length_of_lectures;
            new_module->num_of_practicals = temp_module->num_of_practicals;
            new_module->length_of_practicals = temp_module->length_of_practicals;
            new_module->clashes = temp_module->clashes;

            //we now want to add the new_module to our linked list
            if (*head == NULL) {
                *head = new_module;
                next =  new_module->next;
                return;
            } else {
                    while (next->next != NULL){ next = next->next;}
                    next->next = new_module;
                return;
            }
        }
        temp_module = temp_module->next;
        }
    if (*head != new_module) {
        //reached the end of our modules list without finding the module
        printf("The module: %s \n Was not present in the modules file. \n", module_code);
    }
}


