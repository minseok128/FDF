/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:33:33 by michang           #+#    #+#             */
/*   Updated: 2023/08/08 17:33:34 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map.height)
	{
		j = -1;
		while (++j < data->map.width - 1)
			//bresenham_line(data, data->map.m3d[i][j], data->map.m3d[i][j + 1]);
			bresenham(data, data->map.m3d[i][j], data->map.m3d[i][j + 1]);
	}
	i = -1;
	while (++i < data->map.width)
	{
		j = -1;
		while (++j < data->map.height - 1)
			//bresenham_line(data, data->map.m3d[j][i], data->map.m3d[j + 1][i]);
			bresenham(data, data->map.m3d[j][i], data->map.m3d[j + 1][i]);
	}
}

void	get_trigonometric(t_map *map, double *v)
{
	v[0] = sin(map->angle_3d.x);
	v[1] = cos(map->angle_3d.x);
	v[2] = sin(map->angle_3d.y);
	v[3] = cos(map->angle_3d.y);
	v[4] = sin(map->angle_3d.z);
	v[5] = cos(map->angle_3d.z);
}

void	draw_everthing(t_data *data)
{
	double	v[6];

	get_trigonometric(&(data->map), v);
	interpolate_3d(&(data->map), v);
	draw_map(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	draw_info(data);
}
