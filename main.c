/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:00:00 by michang           #+#    #+#             */
/*   Updated: 2023/07/24 20:00:01 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if ((x >= 0 && y >= 0) && (WIN_HEIGHT > y && WIN_WIDTH > x))
	{
		dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
		*(unsigned int*)dst = color;
	}
}

t_3d_p	interpolate_pixel(t_map *map, t_3d_p p1)
{
	t_3d_p	p2;

	p2.x = p1.x * map->scale + map->offset_2d.x;
	p2.y = p1.y * map->scale + map->offset_2d.y;
	return (p2);
}

void	dda_line(t_data *data, t_3d_p p1, t_3d_p p2)
{
	int steps;
	double	x;
	double	y;
	double	x_inc;
	double	y_inc;

	p1 = interpolate_pixel(&(data->map), p1);
	p2 = interpolate_pixel(&(data->map), p2);
	x = p1.x;
	y = p1.y;
	steps = fmax(fabs(p2.x - p1.x), fabs(p2.y - p1.y));
	x_inc = (p2.x - p1.x) / steps;
	y_inc = (p2.y - p1.y) / steps;
	while (steps-- >= 0)
	{
		my_mlx_pixel_put(data, x, y, 0x00FF0000);
		x += x_inc;
		y += y_inc;
	}
}

// void	put_suqure(t_data *data, double x, double y, double w)
// {
// 	t_3d_p	p1;
// 	t_3d_p	p2;

// 	if (w)
// 	{
// 		p1.x = x;
// 		p1.y = y;
// 		p2.x = x + w;
// 		p2.y = y;
// 		dda_line(data, map, p1, p2);
// 		p2.x = x;
// 		p2.y = y + w;
// 		dda_line(data, map, p1, p2);
// 		p2.x = x + w;
// 		p1.x = x + w;
// 		dda_line(data, map, p1, p2);
// 		p1.x = x;
// 		p1.y = y + w;
// 		dda_line(data, map, p1, p2);
// 	}
// }

void	rotate_xaxis(t_3d_p *p, double theta)
{
	t_3d_p	p2;

	p2.x = p->x;
	p2.y = p->y;
	p2.z = p->z;
	p->y = p2.y * cos(theta) - p2.z * sin(theta);
	p->z = p2.y * sin(theta) + p2.z * cos(theta);
}

void	rotate_yaxis(t_3d_p *p, double theta)
{
	t_3d_p	p2;

	p2.x = p->x;
	p2.y = p->y;
	p2.z = p->z;
	p->x = p2.x * cos(theta) + p2.z * sin(theta);
	p->z = p2.z * cos(theta) - p2.x * sin(theta);
}

void	rotate_zaxis(t_3d_p *p, double theta)
{
	t_3d_p	p2;

	p2.x = p->x;
	p2.y = p->y;
	p2.z = p->z;
	p->x = p2.x * cos(theta) - p2.y * sin(theta);
	p->y = p2.x * sin(theta) + p2.y * cos(theta);
}

void	rotate_3d_mode(t_map *map, int mode, double rot)
{
	int	i;
	int	j;
	double	theta;

	theta = (M_PI / 180) * rot;
	i = 0;
	while (i < (map->height))
	{
		j = 0;
		while (j < (map->width))
		{
			if (mode == 0)
				rotate_xaxis(&(map->m3d[i][j]), theta);
			else if (mode == 1)
				rotate_yaxis(&(map->m3d[i][j]), theta); 
			else
				rotate_zaxis(&(map->m3d[i][j]), theta);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	int	i;
	int j;

	i = -1;
	while (++i < data->map.height)
	{
		j = -1;
		while (++j < data->map.width - 1)
			dda_line(data, data->map.m3d[i][j], data->map.m3d[i][j + 1]);
	}
	i = -1;
	while (++i < data->map.width)
	{
		j = -1;
		while (++j < data->map.height - 1)
			dda_line(data, data->map.m3d[j][i], data->map.m3d[j + 1][i]);
	}
}

void	move_2d(int keycode, t_map *map)
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

void	scale_2d(int keycode, t_map *map)
{
	if (keycode == 12)
		map->scale *= 1.01;
	else if (keycode == 14)
		map->scale *= 0.99;
}

void	rotate_3d(int keycode, t_map *map)
{
	double	delta = 2.5;

	if (keycode == 15)
		rotate_3d_mode(map, 0, 1 * delta);
	else if (keycode == 3)
		rotate_3d_mode(map, 0, -1 * delta);
	else if (keycode == 17)
		rotate_3d_mode(map, 1, 1 * delta);
	else if (keycode == 5)
		rotate_3d_mode(map, 1, -1 * delta);
	else if (keycode == 16)
		rotate_3d_mode(map, 2, 1 * delta);
	else if (keycode == 4)
		rotate_3d_mode(map, 2, -1 * delta);
}

int	keypress_event(int keycode, t_data *data)
{
	//printf("keycode: %d\n", keycode);
	ft_bzero(data->addr, WIN_HEIGHT * WIN_WIDTH * (data->bpp / 8));
	if (keycode == 53)
		exit(0);
	else if (keycode == 0 || keycode == 1
		|| keycode == 2 || keycode == 13)
		move_2d(keycode, &(data->map));
	else if (keycode == 12 || keycode == 14)
		scale_2d(keycode, &(data->map));
	else if (keycode == 15|| keycode == 3 || keycode == 17
		|| keycode == 5 || keycode == 16 || keycode == 4)
		rotate_3d(keycode, &(data->map));
	draw_map(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length,
								&data.endian);

	parse_map(argc, argv, &(data.map));
	

	data.map.offset_2d.x += 1000;
	data.map.offset_2d.y += 500;
	
	rotate_3d_mode(&(data.map), 0, 35.264);
	rotate_3d_mode(&(data.map), 1, 45);
	rotate_3d_mode(&(data.map), 2, -35.264);
	//rotate_3d_mode(&(data.map), 1, 180);
	draw_map(&data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);

	mlx_hook(data.mlx_win, 2, 0, &keypress_event, &data);
	
	mlx_loop(data.mlx);
}