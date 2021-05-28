/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnoriko <rnoriko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 13:33:36 by rnoriko           #+#    #+#             */
/*   Updated: 2021/05/28 19:35:22 by rnoriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_del_node(t_gnl_bonus **head, t_gnl_bonus *current)
{
	t_gnl_bonus	*tmp;

	if (!head || !(*head))
		return ;
	tmp = *head;
	if (tmp == current && !tmp->next)
		*head = NULL;
	else if (tmp == current)
		*head = (*head)->next;
	else
	{
		while (tmp->next != current)
			tmp = tmp->next;
		tmp->next = current->next;
		tmp = current;
	}	
	if (tmp->save)
		free(tmp->save);
	free(tmp);
}

static t_gnl_bonus	*ft_get_or_create_node(int fd, t_gnl_bonus **head)
{
	t_gnl_bonus	*tmp;

	if (!(*head))
	{
		*head = ft_create_node(fd);
		if (!(*head))
			return (NULL);
	}
	tmp = *head;
	while (tmp -> fd != fd)
	{
		if (!tmp -> next)
		{
			tmp -> next = ft_create_node(fd);
			if (!tmp->next)
				return (NULL);
		}
		tmp = tmp -> next;
	}
	return (tmp);
}

static int	ft_save_buffer_node(int fd, char *buffer, t_gnl_bonus **head,
	t_gnl_bonus *current)
{
	char		*control_leaks;
	int			readed_bytes;

	readed_bytes = read(fd, buffer, BUFFER_SIZE);
	while (readed_bytes)
	{
		if (readed_bytes == -1)
		{
			ft_del_node(head, current);
			return (readed_bytes);
		}
		buffer[readed_bytes] = '\0';
		if (current -> save)
		{
			control_leaks = current -> save;
			current -> save = ft_strjoin(current -> save, buffer);
			free(control_leaks);
		}
		else
			current -> save = ft_strjoin(buffer, "");
		if (ft_strchr(buffer, '\n'))
			break ;
		readed_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	return (readed_bytes);
}

static char	*ft_get_line_and_reminder(char **line, char *save,
	int readed_bytes)
{
	char	*control_leaks;
	size_t	i;

	i = 0;
	while (save[i] != '\n' && save[i])
		i++;
	if (i < ft_strlen(save))
	{
		*line = ft_substr(save, 0, i);
		control_leaks = save;
		save = ft_substr(save, i + 1, ft_strlen(save));
		free(control_leaks);
	}
	else if (!readed_bytes)
	{
		*line = save;
		save = NULL;
	}
	return (save);
}

int	get_next_line(int fd, char **line)
{
	static t_gnl_bonus	*head;
	t_gnl_bonus			*current;
	char				buffer[BUFFER_SIZE + 1];
	int					readed_bytes;

	if (!line || BUFFER_SIZE <= 0)
		return (-1);
	current = ft_get_or_create_node(fd, &head);
	if (!current)
		return (-1);
	readed_bytes = ft_save_buffer_node(current -> fd, buffer, &head, current);
	if (readed_bytes == -1)
		return (readed_bytes);
	if (!readed_bytes && !current->save)
		*line = ft_strjoin("", "");
	else
		current -> save = ft_get_line_and_reminder(line, current -> save,
				readed_bytes);
	if (!readed_bytes && !current->save)
	{
		ft_del_node(&head, current);
		return (readed_bytes);
	}
	return (1);
}
