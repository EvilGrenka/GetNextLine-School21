/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnoriko <rnoriko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 23:47:15 by rnoriko           #+#    #+#             */
/*   Updated: 2021/05/27 15:35:04 by rnoriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_save_buffer(char *buffer, char *save_buffer)
{
	char	*control_leaks;

	if (save_buffer)
	{
		control_leaks = save_buffer;
		save_buffer = ft_strjoin(save_buffer, buffer);
		free(control_leaks);
	}
	else
		save_buffer = ft_strdup(buffer);
	return (save_buffer);
}

static char	*ft_get_line_and_reminder(char **line, char *save_buffer,
	int readed_bytes)
{
	char	*control_leaks;
	size_t	i;

	i = 0;
	while (save_buffer[i] != '\n' && save_buffer[i])
		i++;
	if (i < ft_strlen(save_buffer))
	{
		*line = ft_substr(save_buffer, 0, i);
		control_leaks = save_buffer;
		save_buffer = ft_substr(save_buffer, i + 1, ft_strlen(save_buffer));
		free(control_leaks);
	}
	else if (!readed_bytes)
	{
		*line = save_buffer;
		save_buffer = NULL;
	}
	return (save_buffer);
}

int	get_next_line(int fd, char **line)
{
	char			buffer[BUFFER_SIZE + 1];
	int				readed_bytes;
	static char		*save_buffer;

	if (!line || BUFFER_SIZE <= 0)
		return (-1);
	readed_bytes = read(fd, buffer, BUFFER_SIZE);
	while (readed_bytes)
	{
		if (readed_bytes == -1)
			return (readed_bytes);
		buffer[readed_bytes] = '\0';
		save_buffer = ft_save_buffer(buffer, save_buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
		readed_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	if (!readed_bytes && !save_buffer)
		*line = ft_strdup("");
	else
		save_buffer = ft_get_line_and_reminder(line, save_buffer, readed_bytes);
	if (!readed_bytes && !save_buffer)
		return (readed_bytes);
	return (1);
}
