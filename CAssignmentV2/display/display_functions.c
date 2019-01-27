//
// Created by Ben on 12/12/2018.
//

#include "display_functions.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#define DEBUG

//handles a user inquiry on a particular module
void print_module_information(Scheme *schemes,char module_name[MODULE_CODE_LENGTH], int num_of_schemes){
    int num_of_students = 0;
    Module *module = NULL;
    Clash *clash = NULL;

    for(int i =0;i<num_of_schemes;i++){
        Module *next = schemes[i].head;
        while (next != NULL){
            if(strcmp(module_name,next->module_code) ==0){
                num_of_students += schemes[i].num_of_students;
                module = next;
            }
            next = next->next;
        }
    }
    if(module != NULL) {
        printf("The module %s is in semester %d, and has %d lectures which last for %d hours. "
               "It also has %d practicals which last for %d hours. This module is taken by %d students.\n",
               module_name, module->semester, module->num_of_lectures, module->length_of_lectures,
               module->num_of_practicals, module->length_of_practicals, num_of_students);
        clash = module->clashes;
        if(strcmp(clash->clashing_module, "NULL") != 0) {
            printf("This module clashes with the following modules:");
            while (clash != NULL) {
                printf(" %s", clash->clashing_module);
                clash = clash->next;
            }
            printf(".\n");
        } else{
            printf("This module does not clash with any other modules.\n");
        }
    }else{
        printf("The module %s was not registered under any scheme.\n",module_name);
    }
}

//prints a nicely formatted timetable
void print_timetable(Day days[DAYS_IN_WEEK]){
    print_columns();
    for(int i = 0; i<DAYS_IN_WEEK; i++) {
        Lesson *hour0 = days[i].hour[0].next;
        Lesson *hour1 = days[i].hour[1].next;
        Lesson *hour2 = days[i].hour[2].next;
        Lesson *hour3 = days[i].hour[3].next;
        Lesson *hour4 = days[i].hour[4].next;
        Lesson *hour5 = days[i].hour[5].next;
        Lesson *hour6 = days[i].hour[6].next;
        Lesson *hour7 = days[i].hour[7].next;
        Lesson *hour8 = days[i].hour[8].next;
           while (hour0 != NULL ||
                   hour1 != NULL ||
                   hour2 != NULL ||
                   hour3 != NULL ||
                   hour4 != NULL ||
                   hour5 != NULL ||
                   hour6 != NULL ||
                   hour7 != NULL ||
                   hour8 != NULL){

               printf("\n");
               print_day(i);

               if(hour0 != NULL){
                   printf("  %s  ", hour0->modules_being_taught);
                   hour0 = hour0->next;
               } else {
                   printf("            ");
               }
               if(hour1 != NULL){
                   printf("  %s  ", hour1->modules_being_taught);
                   hour1 = hour1->next;
               } else {
                   printf("            ");
               }
               if(hour2 != NULL){
                   printf("  %s  ", hour2->modules_being_taught);
                   hour2 = hour2->next;
               } else {
                   printf("            ");
               }
               if(hour3 != NULL){
                   printf("  %s  ", hour3->modules_being_taught);
                   hour3 = hour3->next;
               } else {
                   printf("            ");
               }
               if(hour4 != NULL){
                   printf("  %s  ", hour4->modules_being_taught);
                   hour4 = hour4->next;
               } else {
                   printf("            ");
               }
               if(hour5 != NULL){
                   printf("  %s  ", hour5->modules_being_taught);
                   hour5 = hour5->next;
               } else {
                   printf("            ");
               }
               if(hour6 != NULL){
                   printf("  %s  ", hour6->modules_being_taught);
                   hour6 = hour6->next;
               } else {
                   printf("            ");
               }
               if(hour7 != NULL){
                   printf("  %s  ", hour7->modules_being_taught);
                   hour7 = hour7->next;
               } else {
                   printf("            ");
               }
               if(hour8 != NULL){
                   printf("  %s  ", hour0->modules_being_taught);
                   hour8 = hour8->next;
               } else {
                   printf("            ");
               }
        }
    }
}


void print_columns() {
    //want to make every 'column' 13 gaps wide
    printf("\n"
    "            "
    "     Day    "
    "      9     "
    "     10     "
    "     11     "
    "     12     "
    "     13     "
    "     14     "
    "     15     "
    "     16     "
    "     17     "
    );
}


//takes an int and prints the appropriate day
void print_day(int day){

    switch (day){
        case 0:
            printf("            "
                   "   Monday  ");
            return;
        case 1:
            printf("            "
                   "  Tuesday  ");
            return;
        case 2:
            printf("            "
                   "Wednesday  ");
            return;
        case 3:
            printf("            "
                   " Thursday  ");
            return;
        case 4:
            printf("            "
                   "   Friday  ");
            return;
        case 5:
            printf("            "
                   " Saturday  ");
            return;
        case 6:
            printf("            "
                   "   Sunday  ");
            return;
        default:
            printf("            "
                   "Invalid Day");
            return;
    }
}