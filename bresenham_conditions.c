/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_conditions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:31:14 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/16 13:14:04 by ishakuro         ###   ########.fr       */
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

int	err_calculation(int dx, int dy)
{
	if (dx > dy)
		return (dx / 2);
	else
		return (-dy / 2);
}

void	zoom(t_p *p1, t_p *p2, t_mlx *mlx)
{
	p1->x *= mlx->zoom;
	p1->y *= mlx->zoom;
	p2->x *= mlx->zoom;
	p2->y *= mlx->zoom;
}
