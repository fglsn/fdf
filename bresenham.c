/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:31:14 by ishakuro          #+#    #+#             */
/*   Updated: 2022/04/05 11:07:19 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso(t_p *p, int z, t_mlx *mlx)
{
	p->x = (p->x - p->y) * cos(mlx->angle);
	p->y = (-z * mlx->raise_z) + (p->x + p->y) * sin(mlx->angle);
}

void	apply_projection(t_p *p1, t_p *p2, t_z *z, t_mlx *mlx)
{
	iso(p1, z->z1, mlx);
	iso(p2, z->z2, mlx);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;
	int		x_calc;
	int		y_calc;

	x_calc = x + mlx->offset_x;
	y_calc = y + mlx->offset_y;
	if (x_calc > 0 && y_calc >= 0 && x_calc < WIN_WIDTH && y_calc < WIN_HEIGHT)
	{
		dst = mlx->addr
			+ (y_calc * mlx->line_length + x_calc * (mlx->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	init_coordinates(t_p *p1, t_p *p2, t_z *z, t_mlx *mlx)
{
	z->z1 = mlx->map->lines[p1->y][p1->x];
	z->z2 = mlx->map->lines[p2->y][p2->x];
	zoom(p1, p2, mlx);
	if (mlx->projection == 1)
		apply_projection(p1, p2, z, mlx);
}

void	bresenham(t_p p1, t_p p2, t_mlx *mlx)
{
	t_z	z;
	t_p	delta;
	int	err;
	int	e2;

	init_coordinates(&p1, &p2, &z, mlx);
	delta = point(ft_abs(p1.x - p2.x), ft_abs(p1.y - p2.y));
	err = err_calculation(&delta);
	while (1)
	{
		my_mlx_pixel_put(mlx, p1.x, p1.y, color(z.z1, z.z2, mlx->map));
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		e2 = err;
		if (e2 > -delta.x)
		{
			err -= delta.y;
			p1.x += ft_direction(p1.x, p2.x);
		}
		if (e2 < delta.y)
		{
			err += delta.x;
			p1.y += ft_direction(p1.y, p2.y);
		}
	}
}
