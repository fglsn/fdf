/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:58:16 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/15 17:05:58 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mlx	*init_fdf(void)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!mlx)
		exit_program(ERROR);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		exit_program(ERROR);
	mlx->window = mlx_new_window(mlx->mlx, 1920, 1080, "Fdf");
	if (!mlx->window)
		exit_program(ERROR);
	mlx->img = mlx_new_image(mlx->mlx, 1920, 1080);
	if (!mlx->img)
		exit_program(ERROR);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	if (!mlx->addr)
		exit_program(ERROR);
	return (mlx);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C

void	bresenham(int x0, int y0, int x1, int y1, t_mlx *mlx)
{
	int	dx;
	int	dy;
	int	err;
	int	e2;

	dx = ft_abs(x1 - x0);
	dy = ft_abs(y1 - y0);
	err = bresenham_err(dx, dy);
	while (1)
	{
		my_mlx_pixel_put(mlx, x0, y0, 0x00FF0000);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += ft_direction(x0, x1);
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += ft_direction(y0, y1);
		}
	}
}

// void	bresenham_algo(t_mlx *mlx, int x, int y, int x1, int y1)
// {
// 	int	x_step;
// 	int	y_step;
// 	int	max;

// 	x_step = ABS(x1 - x);
// 	y_step = ABS(y1 - y);
// 	max = MAX(x_step, y_step);
// 	printf("MAX: %d\n", max); //
// 	x_step /= max;
// 	y_step /= max;
// 	while ((int)(x - x1) || (int)(y - y1))
// 	{
// 		my_mlx_pixel_put(mlx, x, y, 0x00FF0000);
// 		x += x_step;
// 		y += y_step;
// 	}
// }

// void	draw_circle(t_mlx *mlx, int x, int y, int r)
// {
// 	int	i;
// 	double	j1, j2;
// 	int	d;

// 	d = r * 2;
// 	i = x - r;
// 	while (i <= x + r)
// 	{
// 		j1 = sqrt(r * r - (i - x) * (i - x)) + y;
// 		j2 = -j1 + y * 2;
// 		my_mlx_pixel_put(mlx, j1, i, 0x00FF0000);
// 		my_mlx_pixel_put(mlx, j2, i, 0x00FF0000);
// 		i++;
// 	}
// }

int	deal_key(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		exit (0);
	}
	return (0);
}

void	draw(void)
{
	t_mlx	*mlx;

	mlx = init_fdf();
	//draw_circle(mlx, 250, 250, 50);
	bresenham(10, 50, 500, 320, mlx);
	bresenham(50, 10, 320, 500, mlx);
	bresenham(0, 50, 0, 320, mlx);
	bresenham(10, 0, 320, 0, mlx);
	//bresenham_algo(mlx, 3, 3, 600, 350);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img, 0, 0);
	mlx_key_hook(mlx->window, deal_key, mlx);
	mlx_loop(mlx->mlx);
}
