/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 21:02:54 by michang           #+#    #+#             */
/*   Updated: 2023/07/30 21:02:57 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_WIDTH 1980
# define WIN_HEIGHT 1024
# include "./minilibx_mms_20210621/mlx.h"
# include "./get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "./libft/libft.h"

typedef struct	s_3d_p {
	double	x;
	double	y;
	double	z;
}	t_3d_p;

typedef struct s_map {
	int		height;
	int		width;
	t_3d_p	**default_m3d;
	t_3d_p	**m3d;
	t_3d_p	angle_3d;
	t_3d_p	offset_2d;
	double	scale;
	double	z_scale;
} t_map;

typedef struct	s_data {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	t_map	map;
}	t_data;

void	draw_info(t_data *data);
void	parse_map(int argc, char **argv, t_map *map);

#endif
