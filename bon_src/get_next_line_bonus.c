/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:02:17 by michang           #+#    #+#             */
/*   Updated: 2023/08/13 20:02:19 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static char	*make_new_backup(char **backup, char **line)
{
	char	*tmp_backup;
	int		i;
	int		j;

	i = 0;
	while ((*backup)[i] && (*backup)[i] != '\n')
		i++;
	if (!(*backup)[i])
		return (freeing(backup));
	tmp_backup = (char *)malloc((ft_strlen(*backup) - i) * sizeof(char));
	if (!tmp_backup)
	{
		freeing(line);
		return (freeing(backup));
	}
	i++;
	j = 0;
	while ((*backup)[i])
		tmp_backup[j++] = (*backup)[i++];
	tmp_backup[j] = '\0';
	freeing(backup);
	return (tmp_backup);
}

static char	*get_line(char **backup)
{
	char	*tmp_line;
	int		i;

	if (!(*backup)[0])
		return ((char *)(freeing(backup) - 1));
	i = 0;
	while ((*backup)[i] && (*backup)[i] != '\n')
		i++;
	if (!(*backup)[i])
		i--;
	tmp_line = (char *)malloc((i + 2) * sizeof(char));
	if (!tmp_line)
		return (freeing(backup));
	i = 0;
	while ((*backup)[i] && (*backup)[i] != '\n')
	{
		tmp_line[i] = (*backup)[i];
		i++;
	}
	if ((*backup)[i] == '\n')
		tmp_line[i++] = '\n';
	tmp_line[i] = '\0';
	return (tmp_line);
}

static char	*get_backup(int fd, char **backup)
{
	char	*buf;
	int		result;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (freeing(backup));
	result = 1;
	while (!ft_strchr(*backup, '\n') && result)
	{
		result = read(fd, buf, BUFFER_SIZE);
		if (result == -1)
		{
			freeing(&buf);
			return (freeing(backup));
		}
		buf[result] = 0;
		*backup = ft_strjoin_gnl(backup, buf);
		if (!(*backup))
			return (freeing(&buf));
	}
	freeing(&buf);
	return (*backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	backup = get_backup(fd, &backup);
	if (!backup)
		return (0);
	line = get_line(&backup);
	if (!line)
		return (0);
	if ((int)line == -1)
		return (line);
	backup = make_new_backup(&backup, &line);
	return (line);
}
