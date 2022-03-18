/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:09:18 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/18 13:46:41 by ishakuro         ###   ########.fr       */
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
//	mlx_clear_window(mlx->mlx, mlx->window);
	draw(mlx);
	return (0);
}

int	mouse(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	(void)x;
	(void)y;
	mlx = (t_mlx *)param;
	if (button == 4)
		mlx->map->zoom -= 1;
	if (button == 5)
		mlx->map->zoom += 1;
	else if (button == 1)
	{
		mlx->mouse->x = x;
		mlx->mouse->y = y;
		mlx->onclick = 1;
	}
		
//	mlx_clear_window(mlx->mlx, mlx->window);
	draw(mlx);
	return (0);
}

int	mouse_release(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	(void)x;
	(void)y;
	(void)button;
	mlx->onclick = 0;
	return (0);
}

int	mouse_move(int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;

	if (!mlx->onclick)
		return (0);
	mlx->mouse->prev_x = mlx->mouse->x;
	mlx->mouse->prev_y = mlx->mouse->y;
	mlx->mouse->x = x;
	mlx->mouse->y = y;
	mlx->offset_x += x - mlx->mouse->prev_x;
	mlx->offset_y += y - mlx->mouse->prev_y;
//		mlx_clear_window(mlx->mlx, mlx->window);
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
//	mlx_clear_window(mlx->mlx, mlx->window);
	init_img(mlx);
	draw(mlx);
}
