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
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_3d_p	interpolate_pixel(t_map *map, t_3d_p p1)
{
	t_3d_p	p2;

	p2.x = p1.x * map->scale + map->offset_2d.x;
	p2.y = p1.y * map->scale + map->offset_2d.y;
	return (p2);
}

void	dda_line(t_data *data, t_map *map, t_3d_p p1, t_3d_p p2)
{
	int steps;
	double	x;
	double	y;
	double	x_inc;
	double	y_inc;

	p1 = interpolate_pixel(map, p1);
	p2 = interpolate_pixel(map, p2);
	x = p1.x;
	y = p1.y;
	steps = fmax(fabs(p2.x - p1.x), fabs(p2.y - p1.y));
	x_inc = (p2.x - p1.x) / steps;
	y_inc = (p2.y - p1.y) / steps;
	while (steps-- >= 0)
	{
		// if (x < 0 || y < 0 || x > WIN_WIDTH - 1 || y > WIN_HEIGHT - 1)
		// 	continue ;
		my_mlx_pixel_put(data, x, y, 0x00FF0000);
		//my_mlx_pixel_put(data, x, y, 0x00FF0000);
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
	p->y = p->y * cos(theta) - p->z * sin(theta);
	p->z = p->y * sin(theta) + p->z * cos(theta);
}

void	rotate_yaxis(t_3d_p *p, double theta)
{
	p->x = p->x * cos(theta) + p->z * sin(theta);
	p->z = p->z * cos(theta) - p->x * sin(theta);
}

void	rotate_zaxis(t_3d_p *p, double theta)
{
	p->x = p->x * cos(theta) - p->y * sin(theta);
	p->y = p->x * sin(theta) + p->y * cos(theta);
}

void	rotate_3d(t_map *map, int mode, double rot)
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

void	draw_map(t_data *data, t_map *map)
{
	int	i;
	int j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width - 1)
		{
			dda_line(data, map, map->m3d[i][j], map->m3d[i][j + 1]);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height - 1)
		{
			dda_line(data, map, map->m3d[j][i], map->m3d[j + 1][i]);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_map	map;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	img.img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	// for (int i = 0; i < 1024; i++)
	// {
	// 	for (int j = 0; j < 1024; j++)
	// 		my_mlx_pixel_put(&img, 5 + i, 5 + j, 0x00000001 | (i * 256));
	// }
	//t_point p1 = {256, 256};
	//t_point p2 = {512, 512};
	//dda_line(&img, p1, p2);
	//dda_line(&img, p2, p1);

	parse_map(argc, argv, &map);
	// for (int i = 0; i < map.height; i++)
	// {
	// 	for (int j = 0; j < map.info.x; j++)
	// 	{
	// 		//rotate_xaxis(&(map.m3d[i][j].x), &(map.m3d[i][j].y), &(map.m3d[i][j].z), 90);
	// 		rotate_yaxis(&(map.m3d[i][j].x), &(map.m3d[i][j].y), &(map.m3d[i][j].z), 90);
	// 		//rotate_zaxis(&(map.m3d[i][j].x), &(map.m3d[i][j].y), &(map.m3d[i][j].z), 90);
	// 		//put_suqure(&img, 200 + 200 * (map.m3d[i][j][0] / map.m3d[i][j][2]), 200 + 200 * (map.m3d[i][j][1] / map.m3d[i][j][2]), 1);
	// 		put_suqure(&img, ),
	// 			, 1);

	// 		printf("%f %f  %f | ", map.m3d[i][j].x, map.m3d[i][j].y, map.m3d[i][j].z);
	// 	}
	// 	printf("\n");
	// }
	rotate_3d(&map, 2, 35.264);
	rotate_3d(&map, 0, 45);
	rotate_3d(&map, 1, -35.264);
	rotate_3d(&map, 1, 180);
	draw_map(&img, &map);

	map.offset_2d.x += 0;
	map.offset_2d.y += 0;
	draw_map(&img, &map);

	map.offset_2d.x += 1920;
	map.offset_2d.y += 0;
	draw_map(&img, &map);

	map.offset_2d.x += 0;
	map.offset_2d.y += 800;
	draw_map(&img, &map);

	map.offset_2d.x += -1920;
	map.offset_2d.y += 0;
	draw_map(&img, &map);


	// for (int _i = 0; _i < map.height; _i++)
	// {
	// 	for (int _j = 0; _j < map.width; _j++)
	// 		printf("%f |", (map.m3d)[_i][_j].z);
	// 	printf("\n");
	// }

	// map.offset_2d.x += 500;
	// rotate_3d(&map, 0, 90);
	// convert_3d_to_2d(&map);
	// draw_map(&img, &map);
	
	// rotate_3d(&map, 1, 45);
	// convert_3d_to_2d(&map);
	// draw_map(&img, &map);

	// map.offset_2d.x += 500;
	// rotate_3d(&map, 1, 90);
	// convert_3d_to_2d(&map);
	// draw_map(&img, &map);

	// rotate_3d(&map, 2, 90);
	// convert_3d_to_2d(&map);
	// draw_map(&img, &map);

	// rotate_3d(&map, 0, 45);
	// rotate_3d(&map, 1, 35);
	// rotate_3d(&map, 2, 35);
	// convert_3d_to_2d(&map);
	// draw_map(&img, &map);

	
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}