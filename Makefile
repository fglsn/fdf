NAME = fdf
CC = gcc
FLAGS = -Wall -Wextra -Werror
HEADERS = -I$(LIBFT_DIR) -I$(MINILIBX_DIR)

MINILIBX_DIR = ./minilibx/
MINILIBX = ./minilibx/libmlx.a
LIBFT_DIR = ./libft/
LIBFT = ./libft/libft.a

LIBRARIES = -lm -lft -L$(LIBFT_DIR) -L$(MINILIBX_DIR) -lmlx -framework OpenGL -framework AppKit

FUNCTIONS = main.c \
	init.c \
	helpers.c \
	bresenham_conditions.c \
	draw.c \

OBJECTS = $(addprefix $(OBJ_DIR),$(OBJ_FILES))
OBJ_FILES = $(FUNCTIONS:.c=.o)
OBJ_DIR = ./objects/

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(FLAGS) -o $(NAME) $(FUNCTIONS) $(HEADERS) $(LIBRARIES)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(HEADERS) -o $@ -c $< 

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)

clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(LIBFT)
	@rm -f $(NAME)

re: fclean all
	
man:
	man fdf_sourses/minilibx/man/man3/mlx.1

manwindow:
	man fdf_sourses/minilibx/man/man3/mlx_new_window.1

manpixel:
	man fdf_sourses/minilibx/man/man3/mlx_pixel_put.1

manloop:
	man fdf_sourses/minilibx/man/man3/mlx_loop.1

manimage:
	man fdf_sourses/minilibx/man/man3/mlx_new_image.1