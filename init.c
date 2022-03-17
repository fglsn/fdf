/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:29:39 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/17 17:00:00 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = 0;
	map->height = 0;
	map->lines_capacity = 16;
	map->zoom = 50;
	map->lines = malloc(sizeof(int *) * map->lines_capacity);
//	map->z_offset = 0;
	if (!map->lines)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

t_mlx	*init_mlx(t_map *map)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!mlx)
		exit_program(ERROR);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		exit_program(ERROR);
	mlx->window = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "Fdf");
	if (!mlx->window)
		exit_program(ERROR);
	mlx->img = NULL;
	mlx->addr = NULL;
	mlx->offset_x = 200;
	mlx->offset_y = 100;
	mlx->raise_z = 1;
	mlx->angle = 0.523599;
	mlx->map = map;
	return (mlx);
}
