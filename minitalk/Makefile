# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 12:07:41 by msegrans          #+#    #+#              #
#    Updated: 2021/10/29 22:28:50 by msegrans         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS  = -Wall -Wextra -Werror
CC      = gcc $(CFLAGS)
LIB	    = libft/libft.a
SERVER  = server
CLIENT  = client
INCLUDE = libft

.c.o:
	$(CC) -c $< -o $@ -I$(INCLUDE)

all: $(CLIENT) $(SERVER)

$(SERVER): $(LIB) $(SERVER).o
	$(CC) $(SERVER).o $(LIB) -o $(SERVER) -I$(INCLUDE)

$(CLIENT): $(LIB) $(CLIENT).o
	$(CC) $(CLIENT).o $(LIB) -o $(CLIENT) -I$(INCLUDE)

$(LIB):
	$(MAKE) -C libft bonus

clean:
	$(RM) $(SERVER).o $(CLIENT).o
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(SERVER) $(CLIENT)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
