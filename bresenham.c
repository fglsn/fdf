/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:31:14 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/18 10:37:07 by ishakuro         ###   ########.fr       */
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
//	printf("%d %d %d %d %d\n", mlx->map->zoom, p1->x, p1->y, p2->x, p2->y);

}

int	color(int z, int z2, t_map *map)
{
	if (z == 0 && z2 == 0)
		map->color = 0xffe6cc;
	else
		map->color = 0xff8000;
	return (map->color);
}

void	iso(t_p *p, int z, t_mlx *mlx)
{
	p->x = (p->x - p->y) * cos(mlx->angle);
	p->y = (-z * mlx->raise_z) + (p->x + p->y) * sin(mlx->angle);
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
		dst = mlx->addr + (y_calc * mlx->line_length + x_calc * (mlx->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
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

	// z = mlx->map->lines[p1.y][p1.x] + mlx->map->z_offset;
	// z2 = mlx->map->lines[p2.y][p2.x] + mlx->map->z_offset;
	z = mlx->map->lines[p1.y][p1.x];
	z2 = mlx->map->lines[p2.y][p2.x];

	zoom(&p1, &p2, mlx);
	
	if (mlx->projection == 1)
	{
		iso(&p1, z, mlx);
		iso(&p2, z2, mlx);
	}
	// p1.x += mlx->offset_x;
	// p1.y += mlx->offset_y;
	// p2.x += mlx->offset_x;
	// p2.y += mlx->offset_y;

	dx = ft_abs(p1.x - p2.x);
	dy = ft_abs(p1.y - p2.y);
	err = err_calculation(dx, dy);

	while (1)
	{
//		if (p1.x >= WIN_WIDTH || p2.x >= WIN_WIDTH || p1.y  >= WIN_HEIGHT || p2.y >= WIN_HEIGHT)
//			break ;
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
