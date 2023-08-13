/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:02:20 by michang           #+#    #+#             */
/*   Updated: 2023/08/13 20:02:22 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

char	*freeing(char **backup)
{
	if (!backup || !(*backup))
		return (0);
	if (*backup)
	{
		free(*backup);
		*backup = 0;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			new_c;
	char			*str;

	new_c = (char)c;
	str = (char *)s;
	if (str == 0)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == new_c)
			return (str + i);
		i++;
	}
	if (new_c == 0)
		return (str + i);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin_gnl(char **s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*new;

	if (!(*s1))
	{
		(*s1) = (char *)malloc(1 * sizeof(char));
		if (!(*s1))
			return (0);
		else
			(*s1)[0] = '\0';
	}
	s1_len = ft_strlen(*s1);
	s2_len = ft_strlen(s2);
	new = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!new)
		return (freeing(s1));
	i = 0;
	ft_strlcpy(new, *s1, s1_len + 1);
	ft_strlcpy(new + s1_len, s2, s1_len + s2_len + 1);
	freeing(s1);
	return (new);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = 0;
	while (*(src + src_len))
		src_len++;
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (i < dstsize - 1 && i < src_len)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	if (dstsize > 0)
		*(dst + i) = '\0';
	return (src_len);
}
