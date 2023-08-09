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

static t_3d_p interpolate_2d(t_3d_p p1, double scale, t_3d_p offset_2d)
{
	p1.x = (p1.x * scale + offset_2d.x);
	p1.y = (p1.y * scale + offset_2d.y);
	return (p1);
}

static void	draw_map(t_data *data)
{
	int		arr[4];
	t_3d_p	**m3dp;
	double	scale;
	t_3d_p	offset_2d;

	ft_bzero(data->addr, (WIN_HEIGHT) * (WIN_WIDTH) * (data->bpp / 8));
	m3dp = data->map.m3d;
	arr[0] = data->map.height;
	arr[1] = data->map.width;
	scale = data->map.scale;
	offset_2d = data->map.offset_2d;
	arr[2] = -1;
	while (++arr[2] < arr[0])
	{
		arr[3] = -1;
		while (++arr[3] < arr[1] - 1)
			bresenham(data, interpolate_2d(m3dp[arr[2]][arr[3]], scale, offset_2d),
				interpolate_2d(m3dp[arr[2]][arr[3] + 1], scale, offset_2d));
	}
	arr[2] = -1;
	while (++arr[2] < arr[1])
	{
		arr[3] = -1;
		while (++arr[3] < arr[0] - 1)
			bresenham(data, interpolate_2d(m3dp[arr[3]][arr[2]], scale, offset_2d),
				interpolate_2d(m3dp[arr[3] + 1][arr[2]], scale, offset_2d));
	}
	//printf("%f %f %f\n", (m3dp)[0][0].x, (m3dp)[0][0].y, (m3dp)[0][0].z);
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
