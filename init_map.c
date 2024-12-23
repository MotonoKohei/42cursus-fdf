/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmotono <kmotono@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 07:50:20 by kmotono           #+#    #+#             */
/*   Updated: 2024/11/20 11:55:18 by kmotono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

int	count_columns(char *line)
{
	char	**nums;
	int		width;

	width = 0;
	nums = ft_split(line, ' ');
	while (nums[width])
	{
		free(nums[width]);
		width++;
	}
	free(nums);
	return (width);
}

void	calculate_dimensions(int fd, t_map *map)
{
	char	*line;
	int		tmp;

	map->height = 0;
	map->width = INT_MAX;
	line = get_next_line(fd);
	while (line)
	{
		tmp = count_columns(line);
		if (tmp < map->width)
			map->width = tmp;
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	allocate_grid(t_map *map)
{
	int	i;

	map->grid = (int **)malloc(sizeof(int *) * map->height);
	if (!map->grid)
	{
		perror("Error allocating grid memory");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = (int *)malloc(sizeof(int) * map->width);
		if (!map->grid[i])
		{
			perror("Error allocating row memory");
			free_map(map, i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	init_map(const char *filename, t_map *map)
{
	int	fd;

	fd = open_file(filename);
	calculate_dimensions(fd, map);
	fd = open_file(filename);
	allocate_grid(map);
	close(fd);
}
