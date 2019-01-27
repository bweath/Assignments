//
// Created by Ben on 12/12/2018.
// A header file that contains macros and functions that most other files will need
//

#ifndef CASSIGNMENTV2_COMMON_H
#define CASSIGNMENTV2_COMMON_H

#define MODULE_CODE_LENGTH 8
#define SCHEME_CODE_LENGTH 5
#define DAYS_IN_WEEK 7 //defined this just incase the user wants to remove saturday and/or sunday for some reason
#define HOURS_PER_DAY 9
#define NUM_ROOM_TYPES 2
#define MODULE_FILE "\\modules.txt" // "\\modules.txt" for windowsR
#define SCHEME_FILE "\\schemes.txt" // "\\schemes.txt" for windows
#define TIME_FILE "\\times.txt" // "\\times.txt" for windows
#define ROOM_FILE "\\rooms.txt" // "\\rooms.txt" for windows


//A structure to represent modules
typedef struct module{
    char module_code[MODULE_CODE_LENGTH];
    int semester;
    int num_of_lectures;
    int length_of_lectures;
    int num_of_practicals;
    int length_of_practicals;
    struct module* next;
    struct clash* clashes;
}Module;

//A structure that holds all of the clashing modules for a specific module
typedef struct clash{
    char clashing_module[MODULE_CODE_LENGTH];
    struct clash *next;
}Clash;

//A structure to represent schemes
typedef struct scheme{
    char scheme_code[SCHEME_CODE_LENGTH];
    int year_of_study;
    int num_of_students;
    int num_of_modules;
    struct module* head;
}Scheme;

//A structure to represent rooms
typedef struct room{
    char room_type;
    char room_name[26];
    int num_of_rooms;
}Room;

//A structure to represent an hour of teaching
typedef struct hour{
    int available;
    int lecture_room_used;
    int practical_room_used;
    struct lesson *next;

}Hour;

typedef struct lesson{
    char modules_being_taught[MODULE_CODE_LENGTH+1];
    struct lesson *next;
}Lesson;

//A structure to represent a day of teaching
typedef struct day{
    Hour hour[HOURS_PER_DAY];
}Day;



#endif //CASSIGNMENTV2_COMMON_H
