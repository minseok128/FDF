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

static t_3d_p	interpolate_2d(t_3d_p p1, double scale, t_3d_p offset_2d)
{
	p1.x = (p1.x * scale + offset_2d.x);
	p1.y = (p1.y * scale + offset_2d.y);
	return (p1);
}

static t_trick	set_trick(int *arr, char *addr, t_map *map)
{
	t_trick	t;

	ft_bzero(addr, (WIN_HEIGHT) * (WIN_WIDTH) * (map->bpp / 8));
	arr[0] = map->height;
	arr[1] = map->width;
	arr[2] = -1;
	t.addr = addr;
	t.ll = map->line_length;
	t.bpp = map->bpp;
	return (t);
}

static void	draw_map(t_map *map, char *addr)
{
	int		arr[4];
	t_3d_p	**m3dp;
	double	s;
	t_3d_p	offset_2d;
	t_trick	t;

	t = set_trick(arr, addr, map);
	m3dp = map->m3d;
	s = map->scale;
	offset_2d = map->offset_2d;
	while (++arr[2] < arr[0])
	{
		arr[3] = -1;
		while (++arr[3] < arr[1] - 1)
			bresenham(t, interpolate_2d(m3dp[arr[2]][arr[3]], s, offset_2d),
				interpolate_2d(m3dp[arr[2]][arr[3] + 1], s, offset_2d));
	}
	arr[2] = -1;
	while (++arr[2] < arr[1])
	{
		arr[3] = -1;
		while (++arr[3] < arr[0] - 1)
			bresenham(t, interpolate_2d(m3dp[arr[3]][arr[2]], s, offset_2d),
				interpolate_2d(m3dp[arr[3] + 1][arr[2]], s, offset_2d));
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
	t_map	*mapp;

	mapp = &(data->map);
	get_trigonometric(mapp, v);
	interpolate_3d(mapp, v);
	draw_map(mapp, data->addr);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	draw_info(data);
}
