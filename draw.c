/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:58:16 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/16 18:39:28 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	deal_key(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		exit (0);
	}
	if (keycode == 126)
		mlx->offset_y -= 16;
	if (keycode == 125)
		mlx->offset_y += 16;
	if (keycode == 124)
		mlx->offset_x += 16;
	if (keycode == 123)
		mlx->offset_x -= 16;
	mlx_clear_window(mlx->mlx, mlx->window);
	init_img(mlx);
	draw(mlx);
	return (0);
}

// void	iso(t_p *p, int z)
// {
// 	int previous_x;
// 	int previous_y;

// 	previous_x = p->x;
// 	previous_y = p->y;
// 	p->x = (previous_x - previous_y) * cos(0.523599);
// 	p->y = -z + (previous_x + previous_y) * sin(0.523599);
// }

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
			if (x < mlx->map->width - 1)
				bresenham(point(x, y), point(x + 1, y), mlx);
			if (y < mlx->map->height - 1)
				bresenham(point(x, y), point(x, y + 1), mlx);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img, 0, 0);
	destroy_img(mlx);
}
