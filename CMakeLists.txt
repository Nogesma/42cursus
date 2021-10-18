cmake_minimum_required(VERSION 3.20)
project(42cursus C)

set(CMAKE_C_STANDARD 11)

include_directories(get_next_line)

add_executable(42cursus
        get_next_line/get_next_line.c
        get_next_line/get_next_line.h
        get_next_line/get_next_line_utils.c)
