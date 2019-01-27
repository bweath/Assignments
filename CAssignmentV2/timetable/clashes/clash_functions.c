//
// Created by Ben on 12/12/2018.
//

#include "clash_functions.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
//#define DEBUG

void find_clashes(Scheme scheme,Module *orig_mod){
    Module *temp_module; //the module we are getting clashes for
    temp_module = scheme.head; //the module that might clash with our module
    Clash *clash = orig_mod->clashes;


#ifdef DEBUG
    printf("\nChecking clashes for: %s",orig_mod->module_code);
#endif
    while (temp_module != NULL){
        //checks if the module we are inspecting is in the same semester to our module and not actually our module
        if(orig_mod->semester == temp_module->semester && (strcmp(orig_mod->module_code,temp_module->module_code) !=0)) {
#ifdef DEBUG
            printf("\nClashing module found: %s.", temp_module->module_code);
#endif
            //A clash has been found, so create a clash
            Clash *new_clash = malloc(sizeof(Clash));
            strcpy(new_clash->clashing_module, temp_module->module_code);
            new_clash->next = NULL;

            if (strcmp(clash->clashing_module, "NULL")==0) {    //in this case just add the clash to the head of the linked list
                strcpy(clash->clashing_module, new_clash->clashing_module);
            } else{
                while (clash->next != NULL) {
                    //In the below case the clash is already present so break out of the while loop
                    if (strcmp(clash->clashing_module, new_clash->clashing_module) == 0) { break; }
                    clash = clash->next;
                }
                //This will evaluate to true if we just broke out of the while loop because a clash was already present
                if (strcmp(clash->clashing_module, new_clash->clashing_module) == 0) {
#ifdef DEBUG
                    printf(" Clashing Module was already present.");
#endif
                } else {
                    //add the clash to the end of our list if it was not already there
                    clash->next = new_clash;
                }
            }
        }
            //move to the next module in the scheme
            temp_module = temp_module->next;
    }
#ifdef DEBUG
    printf("\nClashes added to: %s\n",orig_mod->module_code);
#endif
}