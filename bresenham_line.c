/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:41:57 by michang           #+#    #+#             */
/*   Updated: 2023/08/08 14:41:58 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if ((x >= 0 && y >= 0) && (WIN_HEIGHT > y && WIN_WIDTH > x))
	{
		dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

static void	bresenham_line3(t_data *data, int arr[], t_3d_p p1)
{
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	while (i < arr[3])
	{
		p1.y += arr[1];
		cnt += arr[2];
		if (cnt >= arr[3])
		{
			p1.x += arr[0];
			cnt -= arr[3];
		}
		my_mlx_pixel_put(data, p1.x, p1.y, p1.c);
		i++;
	}
}

static void	bresenham_line2(t_data *data, int arr[], t_3d_p p1)
{
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	while (i < arr[2])
	{
		p1.x += arr[0];
		cnt += arr[3];
		if (cnt >= arr[2])
		{
			p1.y += arr[1];
			cnt -= arr[2];
		}
		my_mlx_pixel_put(data, p1.x, p1.y, p1.c);
		i++;
	}
}

static void	bresenham_line1(t_data *data, int arr[], t_3d_p p1)
{
	if (arr[2] >= arr[3])
		bresenham_line2(data, arr, p1);
	else
		bresenham_line3(data, arr, p1);
}

void	bresenham_line(t_data *data, t_3d_p p1, t_3d_p p2)
{
	int	arr[4];

	arr[0] = 0;
	arr[1] = 0;
	arr[2] = p2.x - p1.x;
	arr[3] = p2.y - p1.y;
	if (arr[2] < 0)
	{
		arr[0] = -1;
		arr[2] = -arr[2];
	}
	else
		arr[0] = 1;
	if (arr[3] < 0)
	{
		arr[1] = -1;
		arr[3] = -arr[3];
	}
	else
		arr[1] = 1;
	bresenham_line1(data, arr, p1);
}

void	bresenham(t_data *data, t_3d_p p1, t_3d_p p2)
{
	int x1 = round(p1.x);
	int y1 = round(p1.y);
	int x2 = round(p2.x);
	int y2 = round(p2.y);
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;
	while (1)
	{
		my_mlx_pixel_put(data, x1, y1, p1.c);
		if (x1 == x2 && y1 == y2)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}