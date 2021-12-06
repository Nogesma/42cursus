# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 12:07:41 by msegrans          #+#    #+#              #
#    Updated: 2021/10/12 12:07:45 by msegrans         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
CC     = gcc $(CFLAGS)
OBJ    = minishell.o utils.o built_ins.o
NAME   = minishell
LIB    = libft/libft.a
INCLUDE = -Ilibft -I $(HOME)/.brew/Cellar/readline/8.1.1/include
LIBS = -Llibft -lft

ifneq ($(UNAME), Linux)
    LIBS := $(LIBS) -L $(HOME)/.brew/Cellar/readline/8.1.1/lib -lreadline
else
    LIBS := $(LIBS) -ledit
endif

.c.o:
	$(CC) -c $< -o $@ $(INCLUDE)

$(NAME): $(OBJ) $(LIB)
	$(CC) -o $(NAME) $(OBJ) $(INCLUDE) $(LIBS)

all: $(NAME)

$(LIB):
	$(MAKE) -C libft printf

clean:
	$(RM) $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
