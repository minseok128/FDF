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

void	set_bresenham(int *arr, t_3d_p p1, t_3d_p p2)
{
	arr[0] = round(p1.x);
	arr[1] = round(p1.y);
	arr[2] = round(p2.x);
	arr[3] = round(p2.y);
	arr[4] = abs(arr[2] - arr[0]);
	arr[5] = abs(arr[3] - arr[1]);
	arr[6] = (arr[0] < arr[2]) * 2 - 1;
	arr[7] = (arr[1] < arr[3]) * 2 - 1;
	arr[8] = arr[4] - arr[5];
}

void	bresenham(t_data *data, t_3d_p p1, t_3d_p p2)
{
	int	arr[9];

	set_bresenham(arr, p1, p2);
	while (1)
	{
		my_mlx_pixel_put(data, arr[0], arr[1], p1.c);
		if (arr[0] == arr[2] && arr[1] == arr[3])
			break;
		int e2 = 2 * arr[8];
		if (e2 > -arr[5])
		{
			arr[8] -= arr[5];
			arr[0] += arr[6];
		}
		if (e2 < arr[4])
		{
			arr[8] += arr[4];
			arr[1] += arr[7];
		}
	}
}