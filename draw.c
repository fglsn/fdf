/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:58:16 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/18 16:19:33 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_p	point(int x, int y)
{
	t_p	p;

	p.x = x;
	p.y = y;
	return (p);
}

void	init_img(t_mlx *mlx)
{
	mlx->img = mlx_new_image(mlx->mlx, 1920, 1080);
	if (!mlx->img)
		exit_program(IMG_ERROR);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	if (!mlx->addr)
		exit_program(IMG_ERROR);
}

void	destroy_img(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->addr = NULL;
	mlx->img = NULL;
}

void	draw(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	init_img(mlx);
	while (y < mlx->map->height)
	{
		x = 0;
		while (x < mlx->map->width)
		{
			if (x != mlx->map->width - 1)
				bresenham(point(x, y), point(x + 1, y), mlx->z, mlx);
			if (y != mlx->map->height - 1)
				bresenham(point(x, y), point(x, y + 1), mlx->z, mlx);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img, 0, 0);
	destroy_img(mlx);
}
