//
// Created by Ben on 13/12/2018.
//

#ifndef CASSIGNMENTV2_ADVANED_FUNCTIONS_H
#define CASSIGNMENTV2_ADVANED_FUNCTIONS_H
#include "../../common.h"
//attempts to timetable the uni
void advanced_timetable(Scheme schemes[], int num_of_schemes, Hour *hour,int semester, Lesson **next, Room rooms[]);

//Checks to make sure the module does not clash with any lessons in the time slot (returns 1 if there is a clash, 0 if not)
int advanced_check_for_clashes(Clash **clash,Lesson **head, char *mc);

Lesson *advanced_create_lesson_lecture(char mc[MODULE_CODE_LENGTH+1]);

Lesson *advanced_create_lesson_practical(char mc[MODULE_CODE_LENGTH+1]);

#endif //CASSIGNMENTV2_ADVANED_FUNCTIONS_H
