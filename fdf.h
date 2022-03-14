/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:30:08 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/14 15:55:58 by ishakuro         ###   ########.fr       */
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

# define USAGE_ERROR	"Usage: ./fdf <map_file>"
# define OPEN_MAP_ERROR	"Failed to open a map."
# define INIT_MAP_ERROR	"Failed to initialize a map."
# define READ_MAP_ERROR	"Failed to read a map."

typedef struct s_coords
{
	int				z;
	struct s_coords	*next;
}				t_coords;

typedef struct s_map
{
	int		width;
	int		height;
	int		**lines;
	int		lines_capacity; //Size of memory allocated for number of lines (int pointers to lines)
}				t_map;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}				t_point;

t_map	*init_map(void);
int		read_map(const int fd, t_map *map);
int		fill_struct(char **splitted_line, int width, t_map *map);
void	print_map(t_map *map); //temp
void	exit_program(char *str);


#endif