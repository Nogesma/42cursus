SHELL = /bin/sh

CFLAGS := ${CFLAGS}

CC     ?= gcc
LD     ?= gcc

NAME   ?= libft.a

BUILD_DIR ?= ./build
SRC_DIRS ?= .

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS += $(addprefix -I,$(INC_DIRS))

CFLAGS += -Wall -Wextra -Werror
#CFLAGS += -O2 -march=native
#CFLAGS += -g

$(NAME): $(OBJS)
	@$(AR) rcs $(NAME) $(OBJS)

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $(INC_FLAGS) $< -o $@

all: $(NAME)

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
