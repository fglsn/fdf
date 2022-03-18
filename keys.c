/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:09:18 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/18 16:36:01 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	escape(void *param)
{
	(void)param;
	exit (0);
}

void	keyboard_key(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
		exit (0);
	if (keycode == 126)
		mlx->offset_y -= 16;
	if (keycode == 125)
		mlx->offset_y += 16;
	if (keycode == 124)
		mlx->offset_x += 16;
	if (keycode == 123)
		mlx->offset_x -= 16;
	if (keycode == 24 || keycode == 69)
		mlx->map->zoom += 1;
	if (keycode == 27 || keycode == 78)
		mlx->map->zoom -= 1;
	if (keycode == 47)
		mlx->raise_z++;
	if (keycode == 43)
		mlx->raise_z--;
	if (keycode == 20)
		mlx->angle += 0.1;
	if (keycode == 21)
		mlx->angle -= 0.1;
}

void	projection(int keycode, t_mlx *mlx)
{
	if (keycode == 34)
		mlx->projection = 1;
	if (keycode == 31)
		mlx->projection = 0;
}

int	deal_key(int keycode, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	keyboard_key(keycode, mlx);
	projection(keycode, mlx);
	draw(mlx);
	return (0);
}

void	setup_controls(t_mlx *mlx)
{
	mlx_hook(mlx->window, 2, 0, deal_key, mlx);
	mlx_hook(mlx->window, 17, 0, escape, mlx);
	mlx_hook(mlx->window, 4, 0, mouse, mlx);
	mlx_hook(mlx->window, 6, 0, mouse_move, mlx);
	mlx_hook(mlx->window, 5, 0, mouse_release, mlx);
	init_img(mlx);
	draw(mlx);
}
