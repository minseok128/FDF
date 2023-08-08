/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: michang <michang@student.42seoul.k>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/07/24 20:00:00 by michang		   #+#	#+#			 */
/*   Updated: 2023/07/24 20:00:01 by michang		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "fdf.h"

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

void	draw_map(t_data *data)
{
	int	i;
	int j;

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
	if (keycode == 12 && map->scale < 1000)
		map->scale *= 1.02;
	else if (keycode == 14 && map->scale > 0.5)
		map->scale *= 0.98;
}

void	z_scale_3d(int keycode, t_map *map)
{
	if (keycode == 6)
		map->z_scale += 0.08;
	else if (keycode == 7)
		map->z_scale -= 0.08;
}

void	rotate_3d(int keycode, t_map *map)
{
	double	delta = 0.05;

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

void change_view(int keycode, t_map *map)
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
	//printf("keycode: %d\n", keycode);
	ft_bzero(data->addr, (WIN_HEIGHT) * (WIN_WIDTH) * (data->bpp / 8));
	if (keycode == 53)
		exit(0);
	else if (keycode == 0 || keycode == 1
		|| keycode == 2 || keycode == 13)
		move_2d(keycode, &(data->map));
	else if (keycode == 12 || keycode == 14)
		scale_2d(keycode, &(data->map));
	else if (keycode == 6 || keycode == 7)
		z_scale_3d(keycode, &(data->map));
	else if (keycode == 15|| keycode == 3 || keycode == 17
		|| keycode == 5 || keycode == 16 || keycode == 4)
		rotate_3d(keycode, &(data->map));
	else if (keycode >= 18 && keycode <= 21)
		change_view(keycode, &(data->map));
	else
		return (0);
	draw_everthing(data);
	return (0);
}

int	leave_event(int keycode, t_data *data)
{
	exit(0);
	return (0);
}

double	get_distance_from_center(t_3d_p p1)
{
	return (sqrt((p1.x * p1.x) + (p1.y * p1.y)));
}

void	get_default_scale(t_map *map)
{
	int		i;
	int		j;
	int		max_i;
	int		max_j;
	double	max_v;

	interpolate_3d(map);
	max_i = 0;
	max_j = 0;
	max_v = 0;
	i = -1;
	while (++i < (map->height))
	{
		j = -1;
		while (++j < (map->width))
		{
			if (max_v < get_distance_from_center((map->m3d)[i][j]))
			{
				max_i = i;
				max_j = j;
				max_v = get_distance_from_center((map->m3d)[i][j]);
			}
		}
	}
	map->default_scale = (WIN_HEIGHT / 2.5) / max_v;
	map->scale = (WIN_HEIGHT / 2.5) / max_v;
}

void	system_init(char *addr, t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, addr);
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &(data->bpp), &(data->line_length),
								&(data->endian));
	parse_map(addr, &(data->map));
	get_default_scale(&(data->map));
	draw_everthing(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		system_init(argv[1], &data);
		mlx_hook(data.mlx_win, 2, 0, &keypress_event, &data);
		mlx_hook(data.mlx_win, 17, 0, &leave_event, &data);
		mlx_loop(data.mlx);
	}
}
