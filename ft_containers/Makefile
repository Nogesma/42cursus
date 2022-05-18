SHELL = /bin/sh

CXXFLAGS := ${CFLAGS}

CXX ?= g++

INC_FLAGS := -Isrc
LDFLAGS :=

NAME ?= containers

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

CXXFLAGS += -Wall -Wextra -Wshadow
#CXXFLAGS += -Werror
CXXFLAGS += -std=c++98 -pedantic
#CXXFLAGS += -march=native
#CXXFLAGS += -O2
CXXFLAGS += -g3
CXXFLAGS += -fdiagnostics-color
CXXFLAGS += -fsanitize=address


$(NAME): $(OBJS)
	@echo Linking $@
	@$(CXX) $(CXXFLAGS) $(INC_FLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(BUILD_DIR)/%.cpp.o: %.cpp
	@echo Compiling $@
	@mkdir -p $(dir $@)
	@$(CXX) -c  $(CXXFLAGS) $(INC_FLAGS) $< -o $@

all: $(NAME)

clean:
	@rm -rf $(BUILD_DIR)
	@echo Clean done

fclean:
	@rm -rf $(BUILD_DIR)
	@rm -f $(NAME)
	@echo Fclean done

re: fclean all


.PHONY: all clean fclean re
