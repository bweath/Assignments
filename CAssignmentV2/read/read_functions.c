//
// Created by Ben on 12/12/2018.
//

#include "read_functions.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>

void read_all_files(char directory_path[], Module **modules, Scheme schemes[], int number_of_schemes,Room rooms[], Day days[]){
    //calling each of the read functions one by one and filling our data structureschar directory_path[101];

    // First read in data from modules file
    read_module_file(directory_path, modules);

    //Now count the lines in the schemes file and make an array of schemes equal to the amount of lines
    read_schemes_file(directory_path,*modules,schemes, number_of_schemes);


    //creating an array of rooms and reading values into it
    read_rooms_file(directory_path,rooms);

    //creating an array of days(each with an array of hours) and reading values into it
    read_times_file(directory_path, days);

}

// Function that will count the lines in a file
// Used code from https://stackoverflow.com/questions/12733105/c-function-that-counts-lines-in-file
int count_lines(char *temp_directory){
    char directory[101];
    strcpy(directory, temp_directory);
    strcat(directory, SCHEME_FILE);
    FILE* count_lines_file = fopen(directory, "r");
    int lines = 0;
    int end_of_line;
    // Gets characters from the file one by one until it finds the end of line [\n] - when it does it increments lines
    while(!feof(count_lines_file))
    {
        end_of_line = fgetc(count_lines_file);
        if(end_of_line == '\n')
        {
            lines++;
        }
    }
    fclose(count_lines_file);
    return lines;
}