/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:30:08 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/14 14:11:04 by ishakuro         ###   ########.fr       */
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

int		fill_struct(char **splitted_line, int width, t_map *map)
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

int		read_map(const int fd, t_map *map)
{
	int		read_ret;
	char	*line;
	char	**splitted_line;
	int		width;
	int line_count = 0;
	
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
		{
			printf("Splitted line %d at %d: '%s'\n", line_count, width, splitted_line[width]);
			width++;
		}
		if (!fill_struct(splitted_line, width, map))
		{
			ft_arraydel(splitted_line, width);
			ft_strdel(&line);
			return (-1);
		}
		line_count++;
		read_ret = get_next_line(fd, &line);
	}
	return (read_ret);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_map	*map;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fdf <map_file>", 2);
		exit (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Failed to open a map.", 2);
		exit (1);
	}
	map = init_map();
	if (!map)
	{
		ft_putendl_fd("Failed to initialize map.", 2);
		exit (1);
	}
	if (read_map(fd, map) == -1)
	{
		ft_putendl_fd("Failed to read a map.", 2);
		exit (1);
	}
	printf("%d, %d\n", map->width, map->height);
	int	i = 0;
	int j;
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