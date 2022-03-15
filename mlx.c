/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:58:16 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/15 14:12:53 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mlx	*init_fdf(void)
{
	t_mlx *mlx;

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
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	if (!mlx->addr)
		exit_program(ERROR);
	return (mlx);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_circle(t_mlx *mlx, int x, int y, int r)
{
	int	i;
	double	j1, j2;
	int	d;

	d = r * 2;
	i = x - r;
	while (i <= x + r)
	{
		j1 = sqrt(r * r - (i - x) * (i - x)) + y;
		j2 = -j1 + y * 2;
		my_mlx_pixel_put(mlx, j1, i, 0x00FF0000);
		my_mlx_pixel_put(mlx, j2, i, 0x00FF0000);
		i++;
	}
}

int deal_key(int keycode, t_mlx *mlx)
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
	draw_circle(mlx, 250, 250, 50);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img, 0, 0);
	mlx_key_hook(mlx->window, deal_key, mlx);
	mlx_loop(mlx->mlx);
}