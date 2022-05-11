cmake_minimum_required(VERSION 3.20)
project(ft_containers)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_STANDARD 98)

add_compile_options(-Wall -Werror -Wextra)

set(EXEC containers)

include_directories(src)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS src/*.hpp)

message(SOURCES="${SOURCES}")
message(HEADERS="${HEADERS}")

add_executable(${EXEC} ${SOURCES} ${HEADERS})
