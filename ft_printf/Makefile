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
OBJ    = ft_printf.o print1.o print2.o
LIB	   = libft/libft.a
NAME   = libftprintf.a

.c.o:
	$(CC) -c $< -o $@

$(NAME): $(LIB) $(OBJ)
	$(AR) qcs $(NAME) libft/*.o $(OBJ)

all: $(NAME)

$(LIB):
	$(MAKE) -C libft

clean:
	$(RM) $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
