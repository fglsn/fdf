make:
	clang main.c -L /Users/fglsn/Documents/coding/code-server-basecamp/projects/fdf/ -lmlx -framework OpenGL -framework AppKit

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