/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:31:42 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/18 16:31:55 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	draw(mlx);
	return (0);
}
