/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:42:10 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/21 11:07:01 by ishakuro         ###   ########.fr       */
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

int	err_calculation(t_p *delta)
{
	if (delta->x > delta->y)
		return (delta->x / 2);
	else
		return (-delta->y / 2);
}

void	zoom(t_p *p1, t_p *p2, t_mlx *mlx)
{
	p1->x *= mlx->map->zoom;
	p1->y *= mlx->map->zoom;
	p2->x *= mlx->map->zoom;
	p2->y *= mlx->map->zoom;
}

int	color(int z, int z2, t_map *map)
{
	if (z == 0 && z2 == 0)
		map->color = 0xffe6cc;
	else
		map->color = 0xff8000;
	return (map->color);
}
