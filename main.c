/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:30:08 by ishakuro          #+#    #+#             */
/*   Updated: 2022/04/05 12:39:27 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_program(char *str)
{
	ft_putendl_fd(str, 2);
	exit (1);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;
	t_mlx	*mlx;
	t_mouse	*mouse;

	mouse = NULL;
	if (argc != 2)
		exit_program(USAGE_ERROR);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_program(OPEN_MAP_ERROR);
	map = init_map();
	if (!map)
		exit_program(INIT_MAP_ERROR);
	if (read_map(fd, map) == -1)
		exit_program(READ_MAP_ERROR);
	mlx = init_mlx(map);
	draw(mlx);
	setup_controls(mlx);
	mlx_loop(mlx->mlx);
	close(fd);
}
