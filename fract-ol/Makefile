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

#CFLAGS = -Wall -Wextra -Werror
IFLAGS_LINUX = -lmlx -lXext -lX11 -lm -lbsd #-L./mlx -I./mlx -l mlx #-framework OpenGL -framework Appkit -O3
IFLAGS = -Lmlx -Imlx -lmlx -framework OpenGL -framework Appkit
CC     = gcc $(CFLAGS)
OBJ    = main.o
NAME   = fract-ol

.c.o:
	$(CC) -c $< -o $@ $(IFLAGS)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(IFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
