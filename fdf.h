/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:30:08 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/14 11:32:10 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "fdf_sourses/minilibx/mlx.h"
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_coords
{
	int				z;
	struct s_coords	*next;
}				t_coords;

typedef struct s_map
{
	int		width;
	int		heihgt;
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

#endif