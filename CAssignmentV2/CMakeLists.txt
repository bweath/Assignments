cmake_minimum_required(VERSION 3.10)
project(CAssignmentV2 C)

set(CMAKE_C_STANDARD 11)

add_executable(CAssignmentV2 main.c read/modules/module_functions.c read/modules/module_functions.h
        common.h read/schemes/scheme_functions.c read/schemes/scheme_functions.h read/rooms/rooms_functions.c
        read/rooms/rooms_functions.h timetable/clashes/clash_functions.c timetable/clashes/clash_functions.h
        display/display_functions.c display/display_functions.h timetable/simple/simple_functions.c
        timetable/simple/simple_functions.h read/read_functions.c read/read_functions.h read/times/times_functions.c
        read/times/times_functions.h timetable/advanced/advaned_functions.c timetable/advanced/advaned_functions.h)