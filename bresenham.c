/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:31:14 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/17 13:00:22 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}

int	ft_direction(int a, int b)
{
	if (a < b)
		return (1);
	else
		return (-1);
}

int	err_calculation(int dx, int dy)
{
	if (dx > dy)
		return (dx / 2);
	else
		return (-dy / 2);
}

void	zoom(t_p *p1, t_p *p2, t_mlx *mlx)
{
	p1->x *= mlx->map->zoom;
	p1->y *= mlx->map->zoom;
	p2->x *= mlx->map->zoom;
	p2->y *= mlx->map->zoom;
}

int	color(int z, int z2, t_map *map)
{
	if (z == 0 && z2 == 0)
		map->color = 0xffffff;
	else
		map->color = 0x00ff0000;
	return (map->color);
}

void	iso(t_p *p, int z)
{
	p->x = (p->x - p->y) * cos(0.8);
	p->y = -z + (p->x + p->y) * sin(0.8);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + ((y + mlx->offset_y) * mlx->line_length + (x + mlx->offset_x) * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C

void	bresenham(t_p p1, t_p p2, t_mlx *mlx)
{
	int	dx;
	int	dy;
	int	err;
	int	e2;
	int	z;
	int z2;

	z = mlx->map->lines[p1.y][p1.x] + mlx->map->z_offset;
	z2 = mlx->map->lines[p2.y][p2.x] + mlx->map->z_offset;
	zoom(&p1, &p2, mlx);
	iso(&p1, z);
	iso(&p2, z2);

	// p1.x += mlx->offset_x;
	// p1.y += mlx->offset_y;
	// p2.x += mlx->offset_x;
	// p2.y += mlx->offset_y;

	dx = ft_abs(p1.x - p2.x);
	dy = ft_abs(p1.y - p2.y);
	err = err_calculation(dx, dy);

	while (1)
	{
		my_mlx_pixel_put(mlx, p1.x, p1.y, color(z, z2, mlx->map));
		//mlx_pixel_put(mlx->mlx, mlx->window, p1.x, p1.y, color(z, z2, map));
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			p1.x += ft_direction(p1.x, p2.x);
		}
		if (e2 < dy)
		{
			err += dx;
			p1.y += ft_direction(p1.y, p2.y);
		}
	}
}
