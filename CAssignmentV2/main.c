#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "timetable/clashes/clash_functions.h"
#include "timetable/simple/simple_functions.h"
#include "timetable/advanced/advaned_functions.h"
#include "read/read_functions.h"
#include "display/display_functions.h"



int main() {
    char directory_path[101];
    //Will start by asking user for a directory name
    printf("Please enter the directory of your files. \n");
    scanf("%[^\n]", directory_path);

    //we are now going to set up all of our structures, then call a function to read in the values
    Module *modules = NULL;
    int num_of_schemes = count_lines(directory_path);//Counting the lines in the schemes file so that we can make an array of that size
    Scheme schemes[num_of_schemes];
    Room rooms[NUM_ROOM_TYPES];
    Day days[DAYS_IN_WEEK] ={0}; //initialising all variables to 0 (as we want available to be 0 by default)

    //now passing all of these structures into a function to be filled with data
    read_all_files(directory_path, &modules, schemes,num_of_schemes,rooms,days);

    free(modules);//we can now free modules as all modules have been assigned to their schemes


    //populating our modules with the relevant clashing modules
    // note - might want to move this loop to clash_functions.c
    for(int i =0;i<num_of_schemes;i++){
        Module *next = schemes[i].head;
        while (next != NULL){
            find_clashes(schemes[i],next);
            next = next->next;
        }
    }



    //honestly this could all do with being split up into about 8 different functions but I have run out of time
    int choice;
    do{
        char ignore[11];
        printf("What would you like to do?\n 1 = Module Query, 2 = Timetable simple, 3 = Timetable advanced(**NOTE**: this still does not consider length of modules - only the number of rooms)"
               ", 4 = Quit:\n");
        scanf("%[^\n]",ignore);
        scanf(" %i", &choice);
        scanf("%[^\n]",ignore);

        switch (choice){
            case 1: {
                //now we want to read in a module code from the user and search for it
                char temp_module[MODULE_CODE_LENGTH];
                printf("Please enter the module code of the module you wish to Query: \n");
                scanf(" %[^\n]", temp_module);
                //now print the relevant information for the users module
                print_module_information(schemes, temp_module, num_of_schemes);
                break;
            }
            case 2: {
                //in order for you to be able to timetable multiple times with my implementation im almost sure I would
                // need to create a deep copy of schemes, or start a new thread here
                // Im running out of time so i doubt I will get that done but I do think it is possible
                int semester = 0;
                printf("\n Which semester do you want to timetable? (1 or 2):\n");
                while (semester != 1 && semester != 2) {
                    scanf(" %i", &semester);
                    if (semester != 1 && semester != 2) {
                        printf("Please enter the value 1 or 2:\n");
                    }
                    scanf("%[^\n]",ignore);
                }

                for (int i = 0; i < DAYS_IN_WEEK ; i++) {
                    for (int j = 0; j < HOURS_PER_DAY ; j++) {
                        Lesson *lesson = days[i].hour[j].next;
                        timetable(schemes,num_of_schemes, &days[i].hour[j], semester, &lesson);
                    }
                }
                int failed =0;
                for(int i=0;i<num_of_schemes;i++){
                    Module *module = schemes[i].head;
                    while (module != NULL) {
                        if ((module->num_of_lectures > 0 || module->num_of_practicals > 0) &&
                        (module->semester == semester) && schemes[i].num_of_students > 0){
                            printf("Module %s could not have all of its lectures/practicals timetabled.\n", module->module_code);
                            failed =1;

                        }
                        module = module->next;
                    }
                }
                if (failed ==1){
                    printf("\nCould not successfully timetable every module. \n");
                } else{
                    print_timetable(days);
                }
                //used a bit of code from stack overflow here: https://stackoverflow.com/questions/6417158/c-how-to-free-nodes-in-the-linked-list
                //now I want to free all the lessons in our timetable:
                for(int i=0; i<DAYS_IN_WEEK; i++){
                    for (int x=0; x < HOURS_PER_DAY; x++) {
                        Lesson *head = days[i].hour[x].next;
                        {
                            Lesson *tmp;
                            while (head != NULL) {
                                tmp = head;
                                head = head->next;
                                free(tmp);
                            }
                        }
                    }
                }
                printf("\nThank you for using this system.\n");
                choice = 4;
                break;
            }
            case 3:
            {
                //in order for you to be able to timetable multiple times with my implementation im almost sure I would
                // need to create a deep copy of schemes, or start a new thread here
                // Im running out of time so i doubt I will get that done but I do think it is possible
                int semester = 0;
                printf("\n Which semester do you want to timetable? (1 or 2):\n");
                while (semester != 1 && semester != 2) {
                    scanf(" %i", &semester);
                    if (semester != 1 && semester != 2) {
                        printf("Please enter the value 1 or 2:\n");
                    }
                    scanf("%[^\n]",ignore);
                }

                for (int i = 0; i < DAYS_IN_WEEK ; i++) {
                    for (int j = 0; j < HOURS_PER_DAY ; j++) {
                        Lesson *lesson = days[i].hour[j].next;
                        advanced_timetable(schemes,num_of_schemes, &days[i].hour[j], semester, &lesson,rooms);
                    }
                }
                int failed =0;
                for(int i=0;i<num_of_schemes;i++){
                    Module *module = schemes[i].head;
                    while (module != NULL) {
                        if ((module->num_of_lectures > 0 || module->num_of_practicals > 0) &&
                            (module->semester == semester) && schemes[i].num_of_students > 0){
                            printf("Module %s could not have all of its lectures/practicals timetabled.\n", module->module_code);
                            failed =1;

                        }
                        module = module->next;
                    }
                }
                if (failed ==1){
                    printf("\nCould not successfully timetable every module. \n");
                } else{
                    print_timetable(days);
                }
                //used a bit of code from stack overflow here: https://stackoverflow.com/questions/6417158/c-how-to-free-nodes-in-the-linked-list
                //now I want to free all the lessons in our timetable:
                for(int i=0; i<DAYS_IN_WEEK; i++){
                    for (int x=0; x < HOURS_PER_DAY; x++) {
                        Lesson *head = days[i].hour[x].next;
                        {
                            Lesson *tmp;
                            while (head != NULL) {
                                tmp = head;
                                head = head->next;
                                free(tmp);
                            }
                        }
                    }
                }
                printf("\nThank you for using this system.\n");
                choice = 4;
                break;
            }
            case 4:
                printf("Thank you for using this system.\n");
                break;
            default:
                printf("Please enter a valid choice!\n");
                break;
        }
    }while (choice != 4);




    return 0;
}