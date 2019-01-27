//
// Created by Ben on 10/12/2018.
//

#include "module_functions.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
//#define DEBUG

void read_module_file(char *temp_directory, Module **modules) {

    Module *prev = NULL;

    char module_code[MODULE_CODE_LENGTH];
    int semester;
    //this will be used to temporarily store lecture info - eg 3L2
    //length is 5 as info could potentially be 10L1 (I don't think 6 is necessary as 10L10 or 100L1 seem unrealistic)
    char lect_info[5];
    //this will be used to temporarily store lecture info - eg 2P3
    char prac_info[5];

    //making a copy of our directory, so that we can reuse the directory path for our other read file functions
    char directory[101];
    strcpy(directory, temp_directory);
    strcat(directory, MODULE_FILE);

    FILE* modules_file = fopen(directory, "r");
    //going to create an unordered linked list of all the modules, and later try and move all these modules to their correct schemes
    while (fscanf(modules_file, "%[^ ]  %i  %[^ ] %[^\n] ", module_code, &semester, lect_info, prac_info ) != EOF) {

#ifdef DEBUG
        printf("%s %i %s %s \n", module_code, semester, lect_info,prac_info); //FOR DEBUGGING ONLY
#endif
//if our linked list is empty, add to the head
        if(*modules == NULL){
            *modules = create_module(module_code, semester, lect_info,prac_info);
             prev = *modules;
        }else{
            prev->next = create_module(module_code, semester, lect_info,prac_info);
            prev = prev->next;
        }

    }

    fclose(modules_file);
    printf("Module file complete.\n");
}



//function to create module nodes

Module *create_module(char mc[MODULE_CODE_LENGTH], int semester, char lect_info[4], char pract_info[4]){
    int num_of_lects, length_of_lects, num_of_pracs, length_of_pracs, success;
#ifdef DEBUG
    printf("%s        %s \n",lect_info, pract_info);
#endif
    //getting the bits of the lecture information that we care about from what we read in from the file
    //for example if we read in 2L3, we will get 2 and 3. Success will be set to 1 if everything completes successfully
    //found this method on stack overflow: https://stackoverflow.com/questions/1031872/extract-integer-from-char-buffer
    success= sscanf(lect_info, "%dL%d", &num_of_lects, &length_of_lects);
    if (!success) printf("Something went horribly wrong \n");
    //doing the same again for the practicals
    success= sscanf(pract_info, "%dP%d", &num_of_pracs, &length_of_pracs);
    if (!success) printf("Something went horribly wrong \n");

#ifdef DEBUG
    printf("Number of lectures is: %d.\nLength of Lectures is: %d."
           "\nNumber of Practicals is: %d.\nLength of practicals is: %d.\n"
           , num_of_lects, length_of_lects, num_of_pracs, length_of_pracs);
#endif

    //assign all the variables to the module structure
    Module *new_module = malloc(sizeof(Module));

    strcpy(new_module -> module_code, mc);
    new_module->semester = semester;
    new_module->num_of_lectures = num_of_lects;
    new_module->length_of_lectures = length_of_lects;
    new_module->num_of_practicals = num_of_pracs;
    new_module->length_of_practicals = length_of_pracs;
    new_module->next = NULL;
    //creating an instance of clash so that all modules with the same name will point to the same list of clashes
    Clash *clash = malloc(sizeof(struct clash));
    strcpy(clash->clashing_module,"NULL");
    clash->next = NULL;
    new_module->clashes = clash;

    return  new_module;
}
