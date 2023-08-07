/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:04:59 by michang           #+#    #+#             */
/*   Updated: 2023/08/07 16:05:01 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	to_theta(double rotate)
{
	return ((int)((rotate * 180) / M_PI) % 360);
}

static void	draw_info1(t_data *data)
{
	char	*tmp;
	char	*m;

	tmp = ft_itoa(data->map.offset_2d.x);
	if (!tmp)
		exit(1);
	m = ft_strjoin("x: ", tmp);
	if (!m)
		exit(1);
	mlx_string_put(data->mlx, data->mlx_win, 30, 30, 0xFFFFFF, m);
	free(tmp);
	free(m);
	tmp = ft_itoa(data->map.offset_2d.y);
	if (!tmp)
		exit(1);
	m = ft_strjoin("y: ", tmp);
	if (!m)
		exit(1);
	mlx_string_put(data->mlx, data->mlx_win, 30, 60, 0xFFFFFF, m);
	free(tmp);
	free(m);
}

static void	draw_info2(t_data *data)
{
	char	*tmp;
	char	*m;

	tmp = ft_itoa(to_theta(data->map.angle_3d.x));
	if (!tmp)
		exit(1);
	m = ft_strjoin("angle_x: ", tmp);
	if (!m)
		exit(1);
	mlx_string_put(data->mlx, data->mlx_win, 30, 90, 0xFFFFFF, m);
	free(tmp);
	free(m);
	tmp = ft_itoa(to_theta(data->map.angle_3d.y));
	if (!tmp)
		exit(1);
	m = ft_strjoin("angle_y: ", tmp);
	if (!m)
		exit(1);
	mlx_string_put(data->mlx, data->mlx_win, 30, 120, 0xFFFFFF, m);
	free(tmp);
	free(m);
}

static void	draw_info3(t_data *data)
{
	char	*tmp;
	char	*m;

	tmp = ft_itoa(to_theta(data->map.angle_3d.z));
	if (!tmp)
		exit(1);
	m = ft_strjoin("angle_z: ", tmp);
	if (!m)
		exit(1);
	mlx_string_put(data->mlx, data->mlx_win, 30, 150, 0xFFFFFF, m);
	free(tmp);
	free(m);
	tmp = ft_itoa(data->map.scale * 100);
	if (!tmp)
		exit(1);
	m = ft_strjoin("scale: ", tmp);
	if (!m)
		exit(1);
	mlx_string_put(data->mlx, data->mlx_win, 30, 180, 0xFFFFFF, m);
	free(tmp);
	free(m);
}

void	draw_info(t_data *data)
{
	char	*tmp;
	char	*m;

	draw_info1(data);
	draw_info2(data);
	draw_info3(data);
	tmp = ft_itoa(data->map.z_scale * 100);
	if (!tmp)
		exit(1);
	m = ft_strjoin("z_scale: ", tmp);
	if (!m)
		exit(1);
	mlx_string_put(data->mlx, data->mlx_win, 30, 210, 0xFFFFFF, m);
	free(tmp);
	free(m);
}
