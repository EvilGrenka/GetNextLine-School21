/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnoriko <rnoriko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 13:31:20 by rnoriko           #+#    #+#             */
/*   Updated: 2021/05/28 15:06:51 by rnoriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	str_len;

	str_len = 0;
	while (*s++)
		str_len++;
	return (str_len);
}

char	*ft_strchr(const char *s, int c)
{
	char	*temp_s;

	temp_s = (char *)s;
	while (*temp_s)
	{
		if (*temp_s == (char)c)
			return (temp_s);
		temp_s++;
	}
	if ((char)c == '\0')
		return (temp_s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*substr;

	if (!s || len <= 0 || start >= ft_strlen(s))
		return (ft_strjoin("", ""));
	else
	{
		if (ft_strlen(s + start) < len)
			len = ft_strlen(s + start);
		substr = malloc((len + 1) * sizeof(char));
		if (!substr)
			return (NULL);
		i = 0;
		while (s[i] && i < len)
			substr[i++] = s[start++];
		substr[i] = '\0';
		return (substr);
	}
}

t_gnl_bonus	*ft_create_node(int fd)
{
	t_gnl_bonus	*new_node;

	new_node = (t_gnl_bonus *) malloc(sizeof(t_gnl_bonus));
	if (!new_node)
		return (NULL);
	new_node -> fd = fd;
	new_node -> save_buffer = ft_strjoin("", "");
	new_node -> next = NULL;
	return (new_node);
}
