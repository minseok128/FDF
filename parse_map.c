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

static int	get_map_width(char *line)
{
	int	w;
	int	i;

	w = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			w++;
			i++;
			while (line[i] == ' ')
				i++;
		}
		i++;
	}
	return (w);
}

static void	get_map_info(int fd, t_map *map)
{
	int		h;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		exit(1);
	map->width = get_map_width(line);
	h = (int)freeing(&line);
	while ((int)line != -1)
	{
		line = get_next_line(fd);
		if (!line)
			exit(1);
		if ((int)line != -1)
			freeing(&line);
		h++;
	}
	map->height = h;
}

void	init_map(int argc, char *addr, int *fd, t_map *map)
{
	if (argc < 2)
		exit(0);
	map->scale = 15;
	map->z_scale = 0.5;
	map->offset_2d.x = WIN_WIDTH / 2;
	map->offset_2d.y = WIN_HEIGHT / 2;
	map->angle_3d.x = 35.264 * (M_PI / 180);
	map->angle_3d.y = 45 * (M_PI / 180);
	map->angle_3d.z = -35.264 * (M_PI / 180);
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
	map->default_m3d = malloc(sizeof(t_3d_p *) * map->height);
	map->m3d = malloc(sizeof(t_3d_p *) * map->height);
	i = -1;
	while (++i < map->height)
	{
		(map->default_m3d)[i] = malloc(sizeof(t_3d_p) * map->width);
		(map->m3d)[i] = malloc(sizeof(t_3d_p) * map->width);
		line = ft_split(get_next_line(fd), ' ');
		j = -1;
		while (++j < map->width)
		{
			(map->default_m3d)[i][j].y = (i - (map->height / 2));
			(map->default_m3d)[i][j].x = (j - (map->width / 2));
			(map->default_m3d)[i][j].z = ft_atoi(line[j]);
		}
		free(line);
	}
	//printf("w:%d | h:%d\n", map->width, map->height);
	// for (int _i = 0; _i < map->height; _i++)
	// {
	// 	for (int _j = 0; _j < map->width; _j++)
	// 		printf("%f,%f,%f\n", (map->m3d)[_i][_j].x, (map->m3d)[_i][_j].y, (map->m3d)[_i][_j].z);
	// 	printf("\n");
	// }
}
