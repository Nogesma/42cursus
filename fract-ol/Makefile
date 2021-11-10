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

CFLAGS = -Wall -Wextra -Werror -march=native -O3 -fopenmp
IFLAGS_LINUX = -lmlx -lXext -lX11 -lm -lbsd #-L./mlx -I./mlx -l mlx #-framework OpenGL -framework Appkit -O3
IFLAGS = -Lmlx -lmlx -framework OpenGL -framework Appkit
CC     = /Users/msegrans/.brew/opt/llvm/bin/clang $(CFLAGS)
OBJ    = main.o events.o tools.o iterate.o init.o fractal.o
NAME   = fractol
LIB    = libft/libft.a
INCLUDE = -Ilibft -Imlx -I/Users/msegrans/.brew/Cellar/libomp/13.0.0

.c.o:
	$(CC) -c $< -o $@ $(INCLUDE)

$(NAME): $(OBJ) $(LIB)
	$(CC) -o $(NAME) $(OBJ) -L/Users/msegrans/.brew/Cellar/libomp/13.0.0/lib/ $(LIB) $(IFLAGS) $(INCLUDE)

all: $(NAME)

$(LIB):
	$(MAKE) -C libft bonus

clean:
	$(RM) $(NAME)
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
