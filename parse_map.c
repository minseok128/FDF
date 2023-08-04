/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 21:05:17 by michang           #+#    #+#             */
/*   Updated: 2023/07/30 21:05:18 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void get_map_info(int fd, t_map *map)
{
	int		h;
	int		w;
	char	*line;
	int		i;

	line = get_next_line(fd);
	w = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			w++;
		i++;
	}
	h = 1;
	while ((line = get_next_line(fd)))
		h++;
	map->height = h;
	map->width = w;
}

void	init_map(int argc, char *addr, int *fd, t_map *map)
{
	if (argc < 2)
		exit(0);
	map->scale = 10;
	map->offset_2d.x = 0;
	map->offset_2d.y = 0;
	*fd = open(addr, O_RDONLY);
	get_map_info(*fd, map);
	close(*fd);
	*fd = open(addr, O_RDONLY);
}

void	parse_map(int argc, char **argv, t_map *map)
{
	int		i;
	int		j;
	char	**line;
	int		fd;

	init_map(argc, argv[1], &fd, map);
	map->m3d = malloc(sizeof(t_3d_p *) * map->height);
	i = -1;
	while (++i < map->height)
	{
		(map->m3d)[i] = malloc(sizeof(t_3d_p) * map->width);
		line = ft_split(get_next_line(fd), ' ');
		j = 0;
		while (j < map->width)
		{
			(map->m3d)[i][j].x = i * 5;
			(map->m3d)[i][j].y = j * 5;
			(map->m3d)[i][j].z = ft_atoi(line[j]);
			j++;
		}
		free(line);
	}
	// for (int _i = 0; _i < map->height; _i++)
	// {
	// 	for (int _j = 0; _j < map->width; _j++)
	// 		printf("%f |", (map->m3d)[_i][_j].z);
	// 	printf("\n");
	// }
}
