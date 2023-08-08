/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map1.c                                       :+:      :+:    :+:   */
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

	w = 0;
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
		if ((int)line != -1 && line[0] == '\n')
		{
			freeing(&line);
			break ;
		}
		if ((int)line != -1)
			freeing(&line);
		h++;
	}
	map->height = h;
}

static void	init_map(char *addr, int *fd, t_map *map)
{
	map->default_scale = 1;
	map->scale = 1;
	map->z_scale = 1;
	map->min_z = 1.7976931348623157E+308;
	map->max_z = -1.7976931348623157E+308;
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

static void	alloc_map(t_map *map)
{
	int	i;

	map->default_m3d = malloc(sizeof(t_3d_p *) * map->height);
	map->m3d = malloc(sizeof(t_3d_p *) * map->height);
	if (!(map->m3d) || !(map->default_m3d))
		exit(1);
	i = -1;
	while (++i < map->height)
	{
		(map->default_m3d)[i] = malloc(sizeof(t_3d_p) * map->width);
		(map->m3d)[i] = malloc(sizeof(t_3d_p) * map->width);
		if (!((map->m3d)[i]) || !((map->default_m3d)[i]))
			exit(1);
	}
}

void	parse_map(char *addr, t_map *map)
{
	int		i;
	int		j;
	char	**arr;
	char	*line;
	int		fd;

	init_map(addr, &fd, map);
	alloc_map(map);
	i = -1;
	while (++i < map->height)
	{
		line = get_next_line(fd);
		if (!line)
			exit(1);
		arr = ft_split(line, ' ');
		free(line);
		if (!arr)
			exit(1);
		j = -1;
		while (++j < map->width)
		{
			make_point(map, arr[j], i, j);
			free(arr[j]);
		}
		free(arr[j]);
		free(arr);
	}
	close(fd);
	interpolate_z_value(map);
}
