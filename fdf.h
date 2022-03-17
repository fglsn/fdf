/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:30:08 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/17 12:47:35 by ishakuro         ###   ########.fr       */
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

# define ERROR			"MLX error."
# define IMG_ERROR		"Image initialization error."
# define USAGE_ERROR	"Usage: ./fdf <map_file>"
# define OPEN_MAP_ERROR	"Failed to open a map."
# define INIT_MAP_ERROR	"Failed to initialize a map."
# define READ_MAP_ERROR	"Failed to read a map."

typedef struct s_map
{
	int		width;
	int		height;
	int		**lines;
	int		lines_capacity; //Size of memory allocated for number of lines (int pointers to lines)
	int		zoom;
	int		color;
	int		z_offset;
}				t_map;

typedef struct	s_mlx
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
	t_map	*map;
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
int		deal_key(int keycode, t_mlx *mlx);

int		ft_abs(int a);
int		ft_direction(int a, int b);
int		err_calculation(int dx, int dy);
void	bresenham(t_p p1, t_p p2, t_mlx *mlx);

void	zoom(t_p *p1, t_p *p2, t_mlx *mlx);
t_p		point(int x, int y);
void	draw(t_mlx *mlx);

void	init_img(t_mlx *mlx);
void	destroy_img(t_mlx *mlx);

void	exit_program(char *str);
void	print_map(t_map *map);


#endif