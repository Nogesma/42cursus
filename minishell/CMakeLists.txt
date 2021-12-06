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

add_executable(minishell
        minishell.c
        utils.c
        built_ins.c)

TARGET_LINK_LIBRARIES(minishell readline)
