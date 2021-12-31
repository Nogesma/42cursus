cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_C_STANDARD 99)

add_compile_options(-Wall -Werror -Wextra -Ilibft)
add_link_options(-Llibft -lft -lreadline)

include_directories(libft)
include_directories(~/.brew/Cellar/readline/8.1.1/include)
link_directories(libft)
link_directories(~/.brew/Cellar/readline/8.1.1/lib)
#file(GLOB LIBFT libft/*.c)

add_executable(minishell
        minishell.c
        utils.c
        split_better.c
        sort.c
        built_ins/cd.c
        built_ins/echo.c
        built_ins/exit.c
        built_ins/export.c
        built_ins/pwd.c
        built_ins/unset.c
        utils/env.c
        utils/global.c)

TARGET_LINK_LIBRARIES(minishell readline)
TARGET_LINK_LIBRARIES(minishell ft)
