/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:40:08 by michang           #+#    #+#             */
/*   Updated: 2023/08/08 17:40:09 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		else if (line[i] >= '0' && line[i] <= '9')
			res += line[i] - '0';
		i++;
	}
	return (res);
}

void	make_point(t_map *map, char *line, int i, int j)
{
	(map->default_m3d)[i][j].y = (i - (map->height / 2));
	(map->default_m3d)[i][j].x = (j - (map->width / 2));
	(map->default_m3d)[i][j].z = ft_atoi(line) / 2.0;
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
			(map-> default_m3d)[i][j].z -= weight_z;
	}
}

static double	get_distance_from_center(t_3d_p p1)
{
	return (sqrt((p1.x * p1.x) + (p1.y * p1.y)));
}

double	get_default_scale(t_map *map)
{
	int		arr[4];
	double	v[6];
	double	max_v;

	get_trigonometric(map, v);
	interpolate_3d(map, v);
	arr[2] = 0;
	arr[3] = 0;
	max_v = 0;
	arr[0] = -1;
	while (++arr[0] < (map->height))
	{
		arr[1] = -1;
		while (++arr[1] < (map->width))
		{
			if (max_v < get_distance_from_center((map->m3d)[arr[0]][arr[1]]))
			{
				arr[2] = arr[0];
				arr[3] = arr[1];
				max_v = get_distance_from_center((map->m3d)[arr[0]][arr[1]]);
			}
		}
	}
	return ((WIN_HEIGHT / 2) / max_v);
}
