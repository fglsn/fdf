/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:58:16 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/17 17:04:50 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	escape(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		exit (0);
	}
}

void	keyboard_key(int keycode, t_mlx *mlx)
{
	if (keycode == 126)
		mlx->offset_y -= 16;
	if (keycode == 125)
		mlx->offset_y += 16;
	if (keycode == 124)
		mlx->offset_x += 16;
	if (keycode == 123)
		mlx->offset_x -= 16;
	if (keycode == 24)
		mlx->map->zoom += 1;
	if (keycode == 27)
		mlx->map->zoom -= 1;
	if (keycode == 18)
		mlx->raise_z++;
	if (keycode == 19)
		mlx->raise_z--;
	if (keycode == 20)
		mlx->angle += 0.1;
	if (keycode == 21)
		mlx->angle -= 0.1;
}

int	deal_key(int keycode, t_mlx *mlx)
{
	keyboard_key(keycode, mlx);
	escape(keycode, mlx);
	mlx_clear_window(mlx->mlx, mlx->window);
	init_img(mlx);
	draw(mlx);
	return (0);
}

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
				bresenham(point(x, y), point(x + 1, y), mlx);
			if (y != mlx->map->height - 1)
				bresenham(point(x, y), point(x, y + 1), mlx);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img, 0, 0);
	destroy_img(mlx);
}
