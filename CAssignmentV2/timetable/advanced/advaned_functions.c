//
// Created by Ben on 13/12/2018.
//

#include "advaned_functions.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
//#define DEBUG


// so the idea here is to try and timetable every module into the provided hour
// obviously some wont fit. If we get to the end of all the modules and some still have lessons remaining, then the timetable failed
void advanced_timetable(Scheme *schemes, int num_of_schemes, Hour *hour, int semester, Lesson **head, Room *rooms) {
    //goes through every module in every scheme and trys to add it to the time slot
    Lesson *next = NULL;
    next = *head;
    if (hour->available == 1) {
        for (int i = 0; i < num_of_schemes; ++i) {
            if (schemes[i].num_of_students > 0){ // if the scheme has students on it
                Module **mod_head = &schemes[i].head;
                Module *module;
                module = *mod_head;
                while (module != NULL) { //for every module
                    if (module->semester == semester) { //if the module takes place in our semester
                        if (module->num_of_practicals > module->num_of_lectures
                        && hour->practical_room_used < rooms[1].num_of_rooms) { //add a practical
                            if (advanced_check_for_clashes(&module->clashes, &hour->next, module->module_code) == 0) {
                                //module->num_of_practicals--;
                                for (int z =0; z<num_of_schemes; z++){
                                    Module *traverse_module =schemes[z].head;
                                    while (traverse_module != NULL){
                                        if(strcmp(traverse_module->module_code, module->module_code)==0){
                                            traverse_module->num_of_practicals--;
                                        }
                                        traverse_module =traverse_module->next;
                                    }
                                }
                                hour->practical_room_used += 1;
                                Lesson *lesson = advanced_create_lesson_practical(module->module_code);
                                if (*head == NULL) {
                                    *head = lesson;
                                    hour->next =lesson;
                                    next =*head;
                                } else {
                                    while (next->next != NULL) { next = next->next; }
                                    next->next = lesson;
                                }
                            }
                        } else if (module->num_of_lectures > 0
                                   && hour->lecture_room_used < rooms[1].num_of_rooms) { //add a lecture
                            if (advanced_check_for_clashes(&module->clashes, &hour->next, module->module_code) == 0) {
                                //module->num_of_lectures--;
                                for (int z =0; z<num_of_schemes; z++){
                                    Module *traverse_module =schemes[z].head;
                                    while (traverse_module != NULL){
                                        if(strcmp(traverse_module->module_code, module->module_code)==0){
                                            traverse_module->num_of_lectures--;
                                        }
                                        traverse_module =traverse_module->next;
                                    }
                                }
                                hour->lecture_room_used += 1;
                                Lesson *lesson = advanced_create_lesson_lecture(module->module_code);
                                if (*head == NULL) {
                                    *head = lesson;
                                    hour->next =lesson;
                                    next =*head;
                                } else {
                                    while (next->next != NULL) { next = next->next; }
                                    next->next = lesson;
                                }
                            }

                        }
                    }
                    module = module->next;
                }
            }
        }
    }
}

//takes a module and a time slot, checks if that module clashes with any of the modules in the time slot
int advanced_check_for_clashes(Clash **clash_head, Lesson **lesson_head, char *mc){
    Lesson *lesson = *lesson_head;
    while (lesson != NULL) {//if no lessons there can be no clashes
        Clash *clash = *clash_head;
        while (clash != NULL) {//if no clashes just need to check that the current module isnt already being taught
            //using strncmp because we only want to check if the first 7 digits match
            if(strncmp(clash->clashing_module, lesson->modules_being_taught, MODULE_CODE_LENGTH-1) == 0){
                return 1;
            }
            clash = clash->next;
        }
        //just checking to make sure the lesson is not eqaul to the current module
        if (strncmp(mc, lesson->modules_being_taught, MODULE_CODE_LENGTH-1) == 0) {
            return 1; //clash has been found so true
        }
        lesson = lesson->next;
    }
    //if we get here and we havent already returned then there are no clashes
    return 0;
}

Lesson *advanced_create_lesson_lecture(char *mc){
    Lesson *lesson = malloc(sizeof(Lesson));
    strcpy(lesson->modules_being_taught, mc);
    strcat(lesson->modules_being_taught, "L");
    lesson->next = NULL;
    return lesson;
};

Lesson *advanced_create_lesson_practical(char mc[MODULE_CODE_LENGTH+1]){
    Lesson *lesson = malloc(sizeof(Lesson));
    strcpy(lesson->modules_being_taught, mc);
    strcat(lesson->modules_being_taught, "P");
    lesson->next = NULL;
    return lesson;
};