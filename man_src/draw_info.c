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

static int	draw_info0(t_data *data, int y)
{
	mlx_string_put(data->mlx, data->mlx_win, 30,
		y, 0xFFFFFF, "W-A-S-D : move");
	mlx_string_put(data->mlx, data->mlx_win, 30,
		y + 30, 0xFF7E9D, "R-F : rotate x-axis");
	mlx_string_put(data->mlx, data->mlx_win, 30,
		y + 60, 0xA7EEFF, "T-G : rotate y-axis");
	mlx_string_put(data->mlx, data->mlx_win, 30,
		y + 90, 0xCBFF75, "Y-H : rotate z-axis");
	mlx_string_put(data->mlx, data->mlx_win, 30,
		y + 120, 0xFFDC74, "Q-E : scale");
	mlx_string_put(data->mlx, data->mlx_win, 30,
		y + 150, 0xFFA147, "Z-X : z-scale");
	mlx_string_put(data->mlx, data->mlx_win, 30,
		y + 180, 0xFFFFFF, "1-2-3-4 : change view");
	mlx_string_put(data->mlx, data->mlx_win, 30,
		y + 210, 0xFFFFFF, "ESC : exit program");
	return (y + 300);
}

static int	draw_info1(t_data *data, int y)
{
	char	*tmp;
	char	*m;

	tmp = ft_itoa(data->map.offset_2d.x);
	if (!tmp)
		exit(1);
	m = ft_strjoin("x: ", tmp);
	if (!m)
		exit(1);
	mlx_string_put(data->mlx, data->mlx_win, 30, y, 0xFF3000, m);
	free(tmp);
	free(m);
	tmp = ft_itoa(data->map.offset_2d.y);
	if (!tmp)
		exit(1);
	m = ft_strjoin("y: ", tmp);
	if (!m)
		exit(1);
	mlx_string_put(data->mlx, data->mlx_win, 30, y + 30, 0x00A0F3, m);
	free(tmp);
	free(m);
	return (y + 60);
}

static int	draw_info2(t_data *data, int y)
{
	char	*tmp;
	char	*m;

	tmp = ft_itoa(to_theta(data->map.angle_3d.x));
	if (!tmp)
		exit(1);
	m = ft_strjoin("angle_x: ", tmp);
	if (!m)
		exit(1);
	mlx_string_put(data->mlx, data->mlx_win, 30, y, 0xFF7E9D, m);
	free(tmp);
	free(m);
	tmp = ft_itoa(to_theta(data->map.angle_3d.y));
	if (!tmp)
		exit(1);
	m = ft_strjoin("angle_y: ", tmp);
	if (!m)
		exit(1);
	mlx_string_put(data->mlx, data->mlx_win, 30, y + 30, 0xA7EEFF, m);
	free(tmp);
	free(m);
	return (y + 60);
}

static int	draw_info3(t_data *data, int y)
{
	char	*tmp;
	char	*m;

	tmp = ft_itoa(to_theta(data->map.angle_3d.z));
	if (!tmp)
		exit(1);
	m = ft_strjoin("angle_z: ", tmp);
	if (!m)
		exit(1);
	mlx_string_put(data->mlx, data->mlx_win, 30, y, 0xCBFF75, m);
	free(tmp);
	free(m);
	tmp = ft_itoa(data->map.scale * 100);
	if (!tmp)
		exit(1);
	m = ft_strjoin("scale: ", tmp);
	if (!m)
		exit(1);
	mlx_string_put(data->mlx, data->mlx_win, 30, y + 30, 0xFFDC74, m);
	free(tmp);
	free(m);
	return (y + 60);
}

void	draw_info(t_data *data)
{
	char	*tmp;
	char	*m;
	int		y;

	y = 30;
	y = draw_info3(data,
			draw_info2(data, draw_info1(data, draw_info0(data, y))));
	tmp = ft_itoa(data->map.z_scale * 100);
	if (!tmp)
		exit(1);
	m = ft_strjoin("z_scale: ", tmp);
	if (!m)
		exit(1);
	mlx_string_put(data->mlx, data->mlx_win, 30, y, 0xFFA147, m);
	free(tmp);
	free(m);
}
