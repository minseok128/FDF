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
			bresenham_line(data, data->map.m3d[i][j], data->map.m3d[i][j + 1]);
	}
	i = -1;
	while (++i < data->map.width)
	{
		j = -1;
		while (++j < data->map.height - 1)
			bresenham_line(data, data->map.m3d[j][i], data->map.m3d[j + 1][i]);
	}
}

void	draw_everthing(t_data *data)
{
	interpolate_3d(&(data->map));
	draw_map(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	draw_info(data);
}
