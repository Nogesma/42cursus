# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabir <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/22 13:45:33 by hsabir            #+#    #+#              #
#   Updated: 2022/02/23 15:50:01 by                  ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/sh

CXXFLAGS := ${CFLAGS}

CXX ?= g++-11

INC_FLAGS :=
LDFLAGS :=

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	NPROC := $(shell nproc)
else
	NPROC := $(shell sysctl -n hw.ncpu)
endif

MAKEFLAGS += --output-sync=target
MAKEFLAGS += --no-print-directory
MAKEFLAGS += -D_DAR-WIN_UNLIMITED_SELECT

NAME ?= containers

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

CXXFLAGS += -Wall -Wextra -Werror -Wshadow
CXXFLAGS += -std=c++98 -pedantic
#CXXFLAGS += -march=native
#CXXFLAGS += -O2
CXXFLAGS += -g3
CXXFLAGS += -fdiagnostics-color
CXXFLAGS += -fsanitize=address

all:
	@$(MAKE) -j$(NPROC) $(NAME)

$(NAME): $(OBJS)
	@echo Linking $@
	@$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(BUILD_DIR)/%.cpp.o: %.cpp
	@echo Compiling $@
	@mkdir -p $(dir $@)
	@$(CXX) -c  $(CXXFLAGS) $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
	@echo Clean done

fclean:
	@rm -rf $(BUILD_DIR)
	@rm -f $(NAME)
	@echo Fclean done

re: fclean
	@$(MAKE)

.PHONY: all clean fclean re