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

static void	rotate_xaxis(t_3d_p *p, double theta)
{
	t_3d_p	p2;

	p2.x = p->x;
	p2.y = p->y;
	p2.z = p->z;
	p->y = p2.y * cos(theta) - p2.z * sin(theta);
	p->z = p2.y * sin(theta) + p2.z * cos(theta);
}

static void	rotate_yaxis(t_3d_p *p, double theta)
{
	t_3d_p	p2;

	p2.x = p->x;
	p2.y = p->y;
	p2.z = p->z;
	p->x = p2.x * cos(theta) + p2.z * sin(theta);
	p->z = p2.z * cos(theta) - p2.x * sin(theta);
}

static void	rotate_zaxis(t_3d_p *p, double theta)
{
	t_3d_p	p2;

	p2.x = p->x;
	p2.y = p->y;
	p2.z = p->z;
	p->x = p2.x * cos(theta) - p2.y * sin(theta);
	p->y = p2.x * sin(theta) + p2.y * cos(theta);
}

void	interpolate_3d(t_map *map, double v[])
{
	int		i;
	int		j;
	t_3d_p	p2;

	i = -1;
	while (++i < (map->height))
	{
		j = -1;
		while (++j < (map->width))
		{
			map->m3d[i][j] = map->default_m3d[i][j];
			map->m3d[i][j].z *= map->z_scale;
			map->m3d[i][j].y = p2.y * v[1] - p2.z * v[0];
            map->m3d[i][j].z = p2.y * v[0] + p2.z * v[1];
            p2 = map->m3d[i][j];
            map->m3d[i][j].x = p2.x * v[3] + p2.z * v[2];
            map->m3d[i][j].z = p2.z * v[3] - p2.x * v[2];
            p2 = map->m3d[i][j];
            map->m3d[i][j].x = p2.x * v[5] - p2.y * v[4];
            map->m3d[i][j].y = p2.x * v[4] + p2.y * v[5];
		}
	}
}
