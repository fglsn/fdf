/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:51:21 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/14 15:55:26 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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