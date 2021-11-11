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
IFLAGS_LINUX = -Llibft -lmlx -lXext -lX11 -lm -lbsd
IFLAGS = -lmlx -lft -Llibft -Lmlx -framework OpenGL -framework Appkit
CC     = gcc $(CFLAGS)
OBJ    = main.o events.o tools.o iterate.o init.o fractal.o
NAME   = fractol
LIB    = libft/libft.a
MLX    = mlx/libmlx.a
INCLUDE = -Ilibft -Imlx

.c.o:
	$(CC) -c $< -o $@ $(INCLUDE)

$(NAME): $(MLX) $(LIB) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(INCLUDE) $(IFLAGS)

all: $(NAME)

$(LIB):
	$(MAKE) -C libft

$(MLX):
	$(MAKE) -C mlx

clean:
	$(RM) $(OBJ)
	$(MAKE) -C mlx clean
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
