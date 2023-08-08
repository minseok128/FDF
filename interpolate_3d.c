/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate_3d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:41:19 by michang           #+#    #+#             */
/*   Updated: 2023/08/08 16:41:20 by michang          ###   ########.fr       */
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

void	interpolate_3d(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < (map->height))
	{
		j = 0;
		while (j < (map->width))
		{
			map->m3d[i][j] = map->default_m3d[i][j];
			map->m3d[i][j].z *= map->z_scale;
			rotate_xaxis(&(map->m3d[i][j]), map->angle_3d.x);
			rotate_yaxis(&(map->m3d[i][j]), map->angle_3d.y);
			rotate_zaxis(&(map->m3d[i][j]), map->angle_3d.z);
			j++;
		}
		i++;
	}
}
