DEBUG = TRUE

FILES = main.c \
		init.c \
		display.c \
		paint_col.c \
		gen_type.c \
		loop_hook.c \
		key_hooks.c \
		mouse_hooks.c \
		hooks.c \
		read_map.c \
		display_data.c \
		window.c \
		images.c \
		get_next_line.c \
		matrix.c \
		math.c \
		hitbox.c \
		vector2.c \
		vector3.c \
		colors.c \
		png_decoder.c \
		png_block_parser.c \
		png_integrity_checks.c \
		png_parse_zlib.c \
		png_parse_deflate.c \
		png_create_huffman_tree.c \
		png_read_huffman_tree.c \
		png_deflate_code_reader.c \
		png_unfilter_image.c \
		engine.c

CFLAGS = -Llibft -lft -Lft_printf -lftprintf -Lmlx -lmlx -framework OpenGL -framework AppKit
FLAGS = -Wall -Wextra -Werror -Iinc/ -Ift_printf/ -Imlx/ -Ilibft/

ifeq ($(DEGUB), TRUE)
	CFLAGS+= -fsanitize=address -g3 -std=c89 -pedantic
	FLAGS+= -fsanitize=address -g3 -std=c89 -pedantic
endif

SRC_DIR = src
SRC = $(FILES:%=$(SRC_DIR)/%)

NAME = wolf3d

OBJ_DIR = obj
OBJ = $(FILES:%.c=$(OBJ_DIR)/%.o)

LIBS = libft/libft.a ft_printf/libftprintf.a mlx/libmlx.a
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
	$(MAKE) -C mlx/ clean
	$(RM) $(OBJ)

fclean: clean
	@echo "Cleaning target:"
	$(RM) $(NAME)

re: fclean all

soft_re: soft_clean all
