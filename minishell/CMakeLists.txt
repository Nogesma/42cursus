cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_C_STANDARD 99)

add_compile_options(-Wall -Werror -Wextra -Ilib/libft)
add_link_options(-Llib/libft -lft -lreadline)

include_directories(lib/libft)
include_directories(~/.brew/opt/readline/include)
link_directories(lib/libft)
link_directories(~/.brew/opt/readline/lib)

add_executable(minishell
        src/main.c
        src/built-in/cd.c
        src/built-in/echo.c
        src/built-in/env.c
        src/built-in/exit.c
        src/built-in/export.c
        src/built-in/pwd.c
        src/built-in/unset.c
        src/exec/exec.c
        src/utils/pipes.c
        src/parser/parser.c
        src/utils/environ.c
        src/utils/sort.c
        src/utils/global.c
        src/utils/list.c
        src/utils/path.c
        src/utils/setup.c
        src/utils/error.c
        src/utils/parsing.c
        src/parser/cmd_loop.c
        src/parser/wildcard.c
        src/parser/parse_env.c
        src/parser/heredoc.c
        src/parser/redirect.c
        src/parser/syntax/validator.c
        src/parser/syntax/braces.c
        src/parser/syntax/op.c
        src/parser/syntax/pipes.c
        src/parser/syntax/quotes.c
        src/parser/syntax/redirection.c src/parser/redirect_parse.c src/parser/redirect_parse.h src/parser/cmd_loop_utils.c src/parser/cmd_loop_utils.h)

TARGET_LINK_LIBRARIES(minishell readline)
TARGET_LINK_LIBRARIES(minishell ft)
