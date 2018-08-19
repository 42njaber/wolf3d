FILES = main.c \
		init.c \
		display.c \
		gen_type.c \
		loop_hook.c \
		key_hooks.c \
		mouse_hooks.c \
		read_map.c \
		display_data.c \
		window.c \
		images.c \
		get_next_line.c \
		matrix.c \
		hooks.c

CFLAGS = -Llibft -lft -Lft_printf -lftprintf -Lmlx -lmlx -framework OpenGL -framework AppKit

SRC_DIR = src
SRC = $(FILES:%=$(SRC_DIR)/%)

NAME = wolf3d

OBJ_DIR = obj
OBJ = $(FILES:%.c=$(OBJ_DIR)/%.o)

LIBS = libft/libft.a ft_printf/libftprintf.a mlx/libmlx.a
FLAGS = -Wall -Wextra -Werror -Iinc/
CC = gcc
RM = @rm -fv
.PHONY: all, test, clean, fclean, re, force

all: $(NAME)

force:
	@true

libft/libft.a: force
	make -C libft/

ft_printf/libftprintf.a: force
	make -C ft_printf/

mlx/libmlx.a: force
	make -C mlx/

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/wolf3d.h
	@mkdir $(OBJ_DIR) &> /dev/null || true
	$(CC) $(FLAGS) -o $@ -c $< $(MACROS) 

$(NAME): $(LIBS) $(OBJ) Makefile inc/wolf3d.h
	$(CC) $(CFLAGS) -o $@ $(OBJ)

soft_clean:
	@echo "Cleaning target:"
	$(RM) $(NAME)
	@echo "Cleaning objects:"
	$(RM) $(OBJ)

clean:
	@echo "Cleaning objects:"
	$(MAKE) -C libft/ fclean
	$(MAKE) -C ft_printf/ fclean
	$(MAKE) -C mlx/ fclean
	$(RM) $(OBJ)

fclean: clean
	@echo "Cleaning target:"
	$(RM) $(NAME)

re: fclean all

soft_re: soft_clean all
