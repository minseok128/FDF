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

static void	init_map(int argc, char *addr, int *fd, t_map *map)
{
	if (argc < 2)
		exit(0);
	map->scale = 15;
	map->z_scale = 0.5;
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

static int	parse_color(char *line)
{
	int	res;
	int	i;

	line = ft_strchr(line, ',');
	if (!line)
		return (0x00FFFFFF);
	res = 0;
	i = 2;
	while (line[i])
	{
		res *= 16;
		if (ft_isalpha(line[i]))
			res += 10 + (ft_tolower(line[i]) - 'a');
		else if (ft_isdigit(line[i]))
			res += line[i] - '0';
		i++;
	}
	return (res);
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

static void	make_point(t_map *map, char *line, int i, int j)
{
	(map->default_m3d)[i][j].y = (i - (map->height / 2));
	(map->default_m3d)[i][j].x = (j - (map->width / 2));
	(map->default_m3d)[i][j].z = ft_atoi(line);
	(map->default_m3d)[i][j].c = parse_color(line);
	map->min_z = fmin(map->min_z, (map->default_m3d)[i][j].z);
	map->max_z = fmax(map->max_z, (map->default_m3d)[i][j].z);
}

void	interpolate_z_value(t_map *map)
{
	int		i;
	int		j;
	double	weight_z;

	weight_z = (map->max_z - map->min_z) / 2;
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			(map-> default_m3d)[i][j].z -= weight_z;
			printf("%f\n", (map-> default_m3d)[i][j].z);
		}
	}
}

void	parse_map(int argc, char **argv, t_map *map)
{
	int		i;
	int		j;
	char	**line;
	int		fd;

	init_map(argc, argv[1], &fd, map);
	alloc_map(map);
	i = -1;
	while (++i < map->height)
	{
		line = ft_split(get_next_line(fd), ' ');
		if (!line)
			exit(1);
		j = -1;
		while (++j < map->width)
		{
			make_point(map, line[j], i, j);
			free(line[j]);
		}
		free(line);
	}
	close(fd);
	printf("inof_z:%f,%f\n", map->max_z, map->min_z);
	interpolate_z_value(map);
	// for (int _i = 0; _i < map->height; _i++)
	// {
	// 	for (int _j = 0; _j < map->width; _j++)
	// 		printf("%d\n", (map->m3d)[_i][_j].c);
	// 	printf("\n");
	// }
}
