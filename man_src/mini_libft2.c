/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:43:14 by michang           #+#    #+#             */
/*   Updated: 2023/03/15 18:43:18 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				tmp;
	long long		result;
	int				sign;

	i = 0;
	while (ft_isspace(*(str + i)))
		i++;
	sign = 1;
	if (*(str + i) == '-' || *(str + i) == '+')
	{
		if (*(str + i) == '-')
			sign *= -1;
		i++;
	}
	result = 0;
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		tmp = *(str + i) - '0';
		result = result * 10 + tmp;
		i++;
	}
	return ((int)(result * sign));
}

static int	ft_get_size(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		size++;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*new;
	int		sign;

	size = ft_get_size(n);
	new = ft_calloc(size + 1, sizeof(char));
	if (!new)
		return (0);
	sign = 1;
	if (n < 0)
	{
		new[0] = '-';
		sign *= -1;
	}
	else if (n == 0)
		new[0] = '0';
	size--;
	while (n != 0)
	{
		new[size] = n % 10 * sign + '0';
		n /= 10;
		size--;
	}	
	return (new);
}
