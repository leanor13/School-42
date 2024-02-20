/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:25:34 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/20 12:42:32 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(int *new_line, char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i])
	{
		if (!*new_line)
			buffer[j++] = buffer[i];
		if (buffer[i] == '\n')
			*new_line = 0;
		buffer[i++] = '\0';
	}
}

char	*ft_linejoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (free(s1), NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		if (s2[j++] == '\n')
			break ;
	}
	res[i + j] = '\0';
	return (free(s1), res);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			new_line;

	new_line = 1;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		return (NULL);
	}
	while (new_line && (buffer[0] || read(fd, buffer, BUFFER_SIZE)))
	{
		line = ft_linejoin(line, buffer);
		ft_free(&new_line, buffer);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}

