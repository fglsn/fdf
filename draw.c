/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:58:16 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/16 13:12:32 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	deal_key(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		exit (0);
	}
	return (0);
}

// http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C

void	bresenham(t_p p1, t_p p2, t_mlx *mlx)
{
	int	dx;
	int	dy;
	int	err;
	int	e2;

	dx = ft_abs(p1.x - p2.x);
	dy = ft_abs(p1.y - p2.y);
	err = err_calculation(dx, dy);
	zoom(&p1, &p2, mlx);
	while (1)
	{
		my_mlx_pixel_put(mlx, p1.x, p1.y, 0x00FF0000);
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

t_p	point(int x, int y)
{
	t_p	p;

	p.x = x;
	p.y = y;
	return (p);
}

void	draw(t_map	*map, t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x < map->width - 1)
				bresenham(point(x, y), point(x + 1, y), mlx);
			if (y < map->height - 1)
				bresenham(point(x, y), point(x, y + 1), mlx);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img, 0, 0);
	mlx_key_hook(mlx->window, deal_key, mlx);
}
