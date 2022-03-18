/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:09:40 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/18 15:26:50 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
			exit_program(READ_MAP_ERROR);
		width = 0;
		while (splitted_line[width] != NULL)
			width++;
		if (!fill_struct(splitted_line, width, map))
			exit_program(READ_MAP_ERROR);
		read_ret = get_next_line(fd, &line);
	}
	return (read_ret);
}

void	increase_capacity(t_map *map)
{
	int	**new_lines;

	map->lines_capacity = map->lines_capacity * 2;
	new_lines = malloc(sizeof(int *) * map->lines_capacity);
	if (!new_lines)
		exit_program(MALLOC_ERROR);
	ft_memcpy(new_lines, map->lines, map->height * sizeof(int *));
	free(map->lines);
	map->lines = new_lines;
}

int	fill_struct(char **splitted_line, int width, t_map *map)
{
	int	*int_line;
	int	i;

	i = 0;
	if (!map->width)
		map->width = width;
	else if (width != map->width)
		return (0);
	int_line = ft_memalloc(sizeof(int) * (width));
	if (!int_line)
		return (0);
	while (i < width)
	{
		int_line[i] = ft_atoi(splitted_line[i]);
		i++;
	}
	if (map->height == map->lines_capacity)
		increase_capacity(map);
	map->lines[map->height] = int_line;
	map->height++;
	return (1);
}
