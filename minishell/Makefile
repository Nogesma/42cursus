SHELL = /bin/sh

CFLAGS := ${CFLAGS}

CC     ?= gcc
LD     ?= gcc

INC_FLAGS := -Ilib/libft
LIBS := -Llib/libft -lft -lreadline

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	MAKEFLAGS := --jobs=$(shell nproc)
else
	MAKEFLAGS := --jobs=$(shell sysctl -n hw.ncpu)
	INCLUDE += -I$(HOME)/.brew/Cellar/readline/8.1.1/include
    LIBS += -L$(HOME)/.brew/Cellar/readline/8.1.1/lib
endif

MAKEFLAGS += --output-sync=target

NAME ?= minishell

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. Make will incorrectly expand these otherwise.
SRCS := $(shell find $(SRC_DIRS) -name '*.c')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS += $(addprefix -I,$(INC_DIRS))

LIB    := lib/libft/libft.a

CFLAGS += -Wall -Wextra -Werror
#CFLAGS += -O2 -march=native
#CFLAGS += -g

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

$(NAME): $(LIB) $(OBJS)
	$(CC) $(INC_FLAGS) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(INC_FLAGS) $(CFLAGS) $< -o $@

all: $(NAME)

$(LIB):
	$(MAKE) -C lib/libft printf

clean:
	rm -r $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)