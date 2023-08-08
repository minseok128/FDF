/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:27:25 by michang           #+#    #+#             */
/*   Updated: 2023/08/08 17:27:26 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_move_2d(int keycode, t_map *map)
{
	if (keycode == 13)
		map->offset_2d.y -= 10;
	else if (keycode == 1)
		map->offset_2d.y += 10;
	else if (keycode == 0)
		map->offset_2d.x -= 10;
	else if (keycode == 2)
		map->offset_2d.x += 10;
}

static void	set_rotate_3d(int keycode, t_map *map)
{
	double	delta;

	delta = 0.05;
	if (keycode == 15)
		map->angle_3d.x += delta;
	else if (keycode == 3)
		map->angle_3d.x -= delta;
	else if (keycode == 17)
		map->angle_3d.y += delta;
	else if (keycode == 5)
		map->angle_3d.y -= delta;
	else if (keycode == 16)
		map->angle_3d.z += delta;
	else if (keycode == 4)
		map->angle_3d.z -= delta;
}

static void	set_scale(int keycode, t_map *map)
{
	if (keycode == 12 && map->scale < 1000)
		map->scale *= 1.02;
	else if (keycode == 14 && map->scale > 0.5)
		map->scale *= 0.98;
	else if (keycode == 6)
		map->z_scale += 0.08;
	else if (keycode == 7)
		map->z_scale -= 0.08;
}

void	change_view(int keycode, t_map *map)
{
	map->scale = map->default_scale;
	map->offset_2d.x = WIN_WIDTH / 2;
	map->offset_2d.y = WIN_HEIGHT / 2;
	map->angle_3d.x = 0;
	map->angle_3d.y = 0;
	map->angle_3d.z = 0;
	if (keycode == 18)
	{
		map->z_scale = 0.5;
		map->angle_3d.x = 35.264 * (M_PI / 180);
		map->angle_3d.y = 45 * (M_PI / 180);
		map->angle_3d.z = -35.264 * (M_PI / 180);
	}
	else if (keycode == 20)
		map->angle_3d.x = 90 * (M_PI / 180);
	else if (keycode == 21)
		map->angle_3d.y = 90 * (M_PI / 180);
}

int	keypress_event(int keycode, t_data *data)
{
	ft_bzero(data->addr, (WIN_HEIGHT) * (WIN_WIDTH) * (data->bpp / 8));
	if (keycode == 53)
		exit(0);
	else if (keycode == 0 || keycode == 1
		|| keycode == 2 || keycode == 13)
		set_move_2d(keycode, &(data->map));
	else if (keycode == 12 || keycode == 14 || keycode == 6 || keycode == 7)
		set_scale(keycode, &(data->map));
	else if (keycode == 15 || keycode == 3 || keycode == 17 || keycode == 5
		|| keycode == 16 || keycode == 4)
		set_rotate_3d(keycode, &(data->map));
	else if (keycode >= 18 && keycode <= 21)
		change_view(keycode, &(data->map));
	else
		return (0);
	draw_everthing(data);
	return (0);
}
