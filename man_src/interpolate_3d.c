/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate_3d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:47:39 by michang           #+#    #+#             */
/*   Updated: 2023/08/08 22:47:40 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	to_theta(double rotate)
{
	return ((int)((rotate * 180) / M_PI) % 360);
}

static void	set_interpolate_3d(t_map *map, t_3d_p ***m3dp, int *arr)
{
	*m3dp = map->m3d;
	arr[0] = map->height;
	arr[1] = map->width;
	arr[2] = -1;
}

void	interpolate_3d(t_map *map, double v[])
{
	int		arr[4];
	t_3d_p	p2;
	t_3d_p	**m3dp;

	set_interpolate_3d(map, &m3dp, arr);
	while (++arr[2] < arr[0])
	{
		arr[3] = -1;
		while (++arr[3] < arr[1])
		{
			m3dp[arr[2]][arr[3]] = map->default_m3d[arr[2]][arr[3]];
			m3dp[arr[2]][arr[3]].z *= map->z_scale;
			p2 = m3dp[arr[2]][arr[3]];
			m3dp[arr[2]][arr[3]].y = p2.y * v[1] - p2.z * v[0];
			m3dp[arr[2]][arr[3]].z = p2.y * v[0] + p2.z * v[1];
			p2 = m3dp[arr[2]][arr[3]];
			m3dp[arr[2]][arr[3]].x = p2.x * v[3] + p2.z * v[2];
			m3dp[arr[2]][arr[3]].z = p2.z * v[3] - p2.x * v[2];
			p2 = m3dp[arr[2]][arr[3]];
			m3dp[arr[2]][arr[3]].x = p2.x * v[5] - p2.y * v[4];
			m3dp[arr[2]][arr[3]].y = p2.x * v[4] + p2.y * v[5];
		}
	}
}
