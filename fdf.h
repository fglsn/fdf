/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:30:08 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/18 16:33:30 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "fdf_sourses/minilibx/mlx.h"
# include "libft.h"
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>

# include <stdio.h> //temp

# define WIN_WIDTH		1920
# define WIN_HEIGHT		1080

# define MLX_ERROR			"MLX error."
# define IMG_ERROR		"Image initialization error."
# define USAGE_ERROR	"Usage: ./fdf <map_file>"
# define OPEN_MAP_ERROR	"Failed to open a map."
# define INIT_MAP_ERROR	"Failed to initialize a map."
# define READ_MAP_ERROR	"Failed to read a map."
# define MALLOC_ERROR	"Failed to allocate memory."

typedef struct s_map
{
	int		width;
	int		height;
	int		**lines;
	int		lines_capacity;
	int		zoom;
	int		color;
}				t_map;

typedef struct s_mouse
{
	int		x;
	int		y;
	int		prev_x;
	int		prev_y;
}				t_mouse;

typedef struct s_z
{
	int		z1;
	int		z2;
}				t_z;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		offset_x;
	int		offset_y;
	int		raise_z;
	float	angle;
	int		projection;
	t_map	*map;
	t_mouse	*mouse;
	t_z		*z;
	int		onclick;
}				t_mlx;

typedef struct s_p
{
	int		x;
	int		y;
}				t_p;

t_map	*init_map(void);
t_mlx	*init_mlx(t_map *map);

int		read_map(const int fd, t_map *map);
int		fill_struct(char **splitted_line, int width, t_map *map);

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

int		deal_key(int keycode, void *param);
int		escape(void *param);
void	keyboard_key(int keycode, t_mlx *mlx);
void	projection(int keycode, t_mlx *mlx);

void	setup_controls(t_mlx *mlx);

int		ft_abs(int a);
int		ft_direction(int a, int b);
int		err_calculation(int dx, int dy);
void	bresenham(t_p p1, t_p p2, t_z *z, t_mlx *mlx);

void	zoom(t_p *p1, t_p *p2, t_mlx *mlx);
t_p		point(int x, int y);
void	draw(t_mlx *mlx);
int		color(int z, int z2, t_map *map);

void	init_img(t_mlx *mlx);
void	destroy_img(t_mlx *mlx);

int		mouse(int button, int x, int y, void *param);
int		mouse_move(int x, int y, void *param);
int		mouse_release(int button, int x, int y, void *param);

void	exit_program(char *str);
void	print_map(t_map *map);

#endif
