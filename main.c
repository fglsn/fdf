/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:30:08 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/14 15:51:40 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = 0;
	map->height = 0;
	map->lines_capacity = 16;
	map->lines = malloc(sizeof(int *) * map->lines_capacity);
	if (!map->lines)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

int	fill_struct(char **splitted_line, int width, t_map *map)
{
	int	*int_line;
	int	**new_lines;
	int	i;

	i = 0;
	if (!map->width)
		map->width = width;
	else if (width != map->width)
		return (0);
	int_line = malloc(sizeof(int) * (width));
	if (!int_line)
		return (0);
	while (i < width)
	{
		int_line[i] = ft_atoi(splitted_line[i]);
		i++;
	}
	if (map->height == map->lines_capacity)
	{
		map->lines_capacity = map->lines_capacity * 2;
		new_lines = malloc(sizeof(int *) * map->lines_capacity);
		if (!new_lines)
			return (0);
		ft_memcpy(new_lines, map->lines, map->height * sizeof(int *));
		free(map->lines);
		map->lines = new_lines;
	}
	map->lines[map->height] = int_line;
	map->height++;
	return (1);
}

int	read_map(const int fd, t_map *map)
{
	int		read_ret;
	char	*line;
	char	**splitted_line;
	int		width;

	width = 0;
	read_ret = get_next_line(fd, &line);
	while (read_ret == 1)
	{
		splitted_line = ft_strsplit(line, ' ');
		if (!splitted_line)
		{
			ft_strdel(&line);
			return (-1);
		}
		width = 0;
		while (splitted_line[width] != NULL)
			width++;
		if (!fill_struct(splitted_line, width, map))
		{
			ft_arraydel(splitted_line, width);
			ft_strdel(&line);
			return (-1);
		}
		read_ret = get_next_line(fd, &line);
	}
	return (read_ret);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;

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
	print_map(map);
}
