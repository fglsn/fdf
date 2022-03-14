/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:30:08 by ishakuro          #+#    #+#             */
/*   Updated: 2022/03/14 11:46:14 by ishakuro         ###   ########.fr       */
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
	map->heihgt = 0;
	map->lines_capacity = 16;
	map->lines = malloc(sizeof(int) * map->lines_capacity);
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

	if (!map->width)
		map->width = width;
	else if (width != map->width)
		return (0);
	int_line = malloc(sizeof(int) * (width));
	if (!int_line)
		return (0);
	
}

int		read_map(const int fd, t_map *map)
{
	int		read_ret;
	char	*line;
	char	**splitted_line;
	int		width;
	
	width = 0;
	read_ret = 1;
	while (read_ret == 1)
	{
		read_ret = get_next_line(fd, &line);
		splitted_line = ft_strsplit(line, ' ');
		if (!splitted_line)
		{
			ft_strdel(&line)
			return (0);
		}
		while (splitted_line[width] != NULL)
			width++;
		if (!fill_struct(splitted_line, width, map))
		{
			ft_arraydel(splitted_line, width);
			ft_strdel(&line)
			return (0);
		}
		
	}
	return (read_ret);
}

int		main(int argc, char **argv)
{
	const int	fd;
	char		*line;
	t_map		*map;

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
	if (!read_map(fd, map))
	{
		ft_putendl_fd("Failed to read a map.", 2);
		exit (1);
	}
}