/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:29:39 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/18 16:40:35 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = ft_memalloc(sizeof(t_map));
	if (!map)
		exit_program(MALLOC_ERROR);
	map->width = 0;
	map->height = 0;
	map->lines_capacity = 16;
	map->zoom = 50;
	map->lines = ft_memalloc(sizeof(int *) * map->lines_capacity);
	if (!map->lines)
		exit_program(MALLOC_ERROR);
	return (map);
}

t_mlx	*init_mlx(t_map *map)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)ft_memalloc(sizeof(t_mlx));
	if (!mlx)
		exit_program(MLX_ERROR);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		exit_program(MLX_ERROR);
	mlx->window = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "Fdf");
	if (!mlx->window)
		exit_program(MLX_ERROR);
	mlx->mouse = (t_mouse *)ft_memalloc(sizeof(t_mouse));
	if (!mlx->mouse)
		exit_program(MALLOC_ERROR);
	mlx->z = (t_z *)ft_memalloc(sizeof(t_z));
	if (!mlx->z)
		exit_program(MALLOC_ERROR);
	mlx->img = NULL;
	mlx->addr = NULL;
	mlx->offset_x = 200;
	mlx->offset_y = 200;
	mlx->raise_z = 1;
	mlx->angle = 0.523599;
	mlx->projection = 1;
	mlx->onclick = 0;
	mlx->map = map;
	return (mlx);
}
