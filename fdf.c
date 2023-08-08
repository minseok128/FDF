/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:22:44 by michang           #+#    #+#             */
/*   Updated: 2023/08/08 17:22:45 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	leave_event(int keycode, t_data *data)
{
	exit(0);
	return (0);
}

void	system_init(char *addr, t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, addr);
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &(data->bpp),
			&(data->line_length), &(data->endian));
	parse_map(addr, &(data->map));
	data->map.default_scale = get_default_scale(&(data->map));
	data->map.scale = data->map.default_scale;
	draw_everthing(data);
}

int	is_valid_addr(char *addr)
{
	int	i;

	i = ft_strlen(addr) - 1;
	while (i >= 0 && addr[i] != '.')
		i--;
	if (i == -1)
		return (0);
	return ((addr + i)[0] == '.' && (addr + i)[1] == 'f'
		&& (addr + i)[2] == 'd' && (addr + i)[3] == 'f');
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2 && is_valid_addr(argv[1]))
	{
		system_init(argv[1], &data);
		mlx_hook(data.mlx_win, 2, 0, &keypress_event, &data);
		mlx_hook(data.mlx_win, 17, 0, &leave_event, &data);
		mlx_loop(data.mlx);
	}
	else
		exit(1);
	return (0);
}
