SHELL = /bin/sh

CXXFLAGS := ${CFLAGS}

CXX ?= g++

INC_FLAGS := -Iincludes

NAME ?= containers
STD_NAME ?= std_containers

SRC_DIRS ?= ./src

SRC := src/main.cpp

CXXFLAGS += -Wall -Wextra -Wshadow
CXXFLAGS += -Werror
#CXXFLAGS += -march=native
#CXXFLAGS += -O2
#CXXFLAGS += -flto
#CXXFLAGS += -g3
CXXFLAGS += -fdiagnostics-color
CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer

CVERSION = -std=c++98 -pedantic

all: $(NAME) $(STD_NAME)

$(NAME):
	$(CXX) $(CXXFLAGS) $(CVERSION) $(INC_FLAGS) $(SRC) -o $(NAME)

$(STD_NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(SRC) -DUSE_STD_NAMESPACE=1 -o $(STD_NAME)

clean:
	@echo Nothing to do

fclean:
	@rm -f $(NAME)
	@rm -f $(STD_NAME)
	@echo Fclean done

re: fclean all


.PHONY: all clean fclean re std
