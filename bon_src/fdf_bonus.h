/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:02:06 by michang           #+#    #+#             */
/*   Updated: 2023/08/13 20:02:08 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H
# include "../minilibx_mms_20210621/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

typedef struct s_3d_p {
	double	x;
	double	y;
	double	z;
	int		c;
}	t_3d_p;

typedef struct s_map {
	int		bpp;
	int		line_length;
	int		height;
	int		width;
	double	max_z;
	double	min_z;
	t_3d_p	**default_m3d;
	t_3d_p	**m3d;
	t_3d_p	angle_3d;
	t_3d_p	offset_2d;
	double	default_scale;
	double	scale;
	double	z_scale;
}	t_map;

typedef struct s_data {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		endian;
	t_map	map;
}	t_data;

typedef struct s_tric {
	char	*addr;
	int		bpp;
	int		ll;
}	t_trick;

char	*get_next_line(int fd);
int		ft_tolower(int c);
char	*ft_strjoin_gnl(char **s1, char *s2);
char	*freeing(char **backup);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalpha(int c);
char	**ft_split(const char *str, char c);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
void	parse_map(char *addr, t_map *map);
void	bresenham_line(t_data *data, t_3d_p p1, t_3d_p p2);
void	interpolate_3d(t_map *map, double v[]);
int		keypress_event(int keycode, t_data *data);
void	draw_everthing(t_data *data);
void	draw_info(t_data *data);
void	make_point(t_map *map, char *line, int i, int j);
void	interpolate_z_value(t_map *map);
double	get_default_scale(t_map *map);
void	change_view(int keycode, t_map *map);
int		leave_event(int keycode, t_data *data);
void	get_trigonometric(t_map *map, double *value);
int		ft_get_size_of_arr(char *str, char c);
void	bresenham(t_trick t, t_3d_p p1, t_3d_p p2);
int		to_theta(double rotate);

#endif
