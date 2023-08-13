/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:00:21 by michang           #+#    #+#             */
/*   Updated: 2023/08/13 20:00:24 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	set_bresenham(int *a, t_3d_p p1, t_3d_p p2)
{
	a[0] = round(p1.x);
	a[1] = round(p1.y);
	a[2] = round(p2.x);
	a[3] = round(p2.y);
	a[4] = abs(a[2] - a[0]);
	a[5] = abs(a[3] - a[1]);
	a[6] = (a[0] < a[2]) * 2 - 1;
	a[7] = (a[1] < a[3]) * 2 - 1;
	a[8] = a[4] - a[5];
}

void	bresenham(t_trick t, t_3d_p p1, t_3d_p p2)
{
	int	a[10];

	set_bresenham(a, p1, p2);
	while (1)
	{
		if ((a[0] >= 0 && a[1] >= 0) && (WIN_HEIGHT > a[1] && WIN_WIDTH > a[0]))
			*(int *)(t.addr + (a[1] * t.ll + a[0] * (t.bpp / 8))) = p1.c;
		if (a[0] == a[2] && a[1] == a[3])
			break ;
		a[9] = 2 * a[8];
		if (a[9] > -a[5])
		{
			a[8] -= a[5];
			a[0] += a[6];
		}
		if (a[9] < a[4])
		{
			a[8] += a[4];
			a[1] += a[7];
		}
	}
}
