cmake_minimum_required(VERSION 3.20)
project(ft_containers)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_STANDARD 98)

add_compile_options(-Wall -Werror -Wextra)

set(EXEC containers)

include_directories(includes)

add_executable(${EXEC} src/main.cpp)
