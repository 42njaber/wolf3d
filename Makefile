FILES = main.c \
		init.c \
		display.c \
		loop_hook.c \
		key_hooks.c \
		mouse_hooks.c \
		hooks.c

CFLAGS = -Llibgxns -lgxns -framework OpenGL -framework AppKit

SRC_DIR = src
SRC = $(FILES:%=$(SRC_DIR)/%)

NAME = wolf3d

OBJ_DIR = obj
OBJ = $(FILES:%.c=$(OBJ_DIR)/%.o)

LIB = libgxns/libgxns.a
FLAGS = -Wall -Wextra -Werror -Iinc/ 
CC = gcc
RM = @rm -fv
TEST_FILE = test.out
.PHONY: all, test, clean, fclean, re, force

all: $(NAME)

force:
	@true

libgxns/libgxns.a: force
	make -C libgxns/

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/wolf.h
	@mkdir $(OBJ_DIR) &> /dev/null || true
	$(CC) $(FLAGS) -o $@ -c $< $(MACROS) 

$(NAME): $(LIB) $(OBJ) Makefile inc/wolf.h
	$(CC) $(CFLAGS) -o $@ $(OBJ)

soft_clean:
	make -C libgxns/ soft_clean
	@echo "Cleaning target:"
	$(RM) $(NAME)
	@echo "Cleaning objects:"
	$(RM) $(OBJ)

clean:
	@echo "Cleaning objects:"
	$(MAKE) -C libgxns/ fclean
	$(RM) $(OBJ)

fclean: clean
	@echo "Cleaning target:"
	$(RM) $(NAME)

re: fclean all

soft_re: soft_clean all
