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

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS += $(addprefix -I,$(INC_DIRS))

LIB    := lib/libft/libft.a

CFLAGS += -Wall -Wextra -Werror
#CFLAGS += -O2 -march=native
#CFLAGS += -g

$(NAME): $(LIB) $(OBJS)
	@echo Linking $@
	@$(CC) $(INC_FLAGS) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(BUILD_DIR)/%.c.o: %.c
	@echo Compiling $@
	@mkdir -p $(dir $@)
	@$(CC) -c $(INC_FLAGS) $(CFLAGS) $< -o $@

all: $(NAME)

$(LIB):
	@$(MAKE) -C lib/libft
	@echo Libft done

clean:
	@rm -r $(BUILD_DIR)
	@$(MAKE) -C lib/libft clean
	@echo Clean done

fclean:
	@rm -r $(BUILD_DIR)
	@rm $(NAME)
	@$(MAKE) -C lib/libft fclean
	@echo Fclean done

re: fclean all

.PHONY: all clean fclean re
