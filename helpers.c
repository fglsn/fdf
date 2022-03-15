/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:51:21 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/15 17:03:36 by ishakuro         ###   ########.fr       */
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

int	bresenham_err(int dx, int dy)
{
	if (dx > dy)
		return (dx / 2);
	else
		return (-dy / 2);
}


void	exit_program(char *str)
{
	ft_putendl_fd(str, 2);
	exit (1);
}

void	print_map(t_map *map) //temp function
{
	int	i;
	int	j;

	i = 0;
	printf("%d, %d\n", map->width, map->height);
	while (i < map->height)
	{
		j = 0;
		while (j != map->width)
		{
			printf("%d ", map->lines[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}