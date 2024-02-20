/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:25:34 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/20 19:47:54 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_linelen(char *str)
{
	int	ctd;

	ctd = 0;
	while (str && str[ctd] && str[ctd] != '\n')
		ctd++;
	if (str && str[ctd] == '\n')
		ctd++;
	return (ctd);
}

char	*ft_join_line(char *s1, char *s2)
{
	int		ctd;
	int		ctd2;
	char	*str;

	ctd = 0;
	str = (char *)malloc(ft_linelen(s1) + ft_linelen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1 && s1[ctd])
	{
		str[ctd] = s1[ctd];
		ctd++;
	}
	ctd2 = 0;
	while (s2[ctd2] != '\n' && s2[ctd2])
	{
		str[ctd + ctd2] = s2[ctd2];
		ctd2++;
	}
	if (s2[ctd2] == '\n')
		str[ctd + ctd2++] = '\n';
	str[ctd + ctd2] = '\0';
	if (s1)
		free(s1);
	return (str);
}

void	line_buffer_clean(char *str)
{
	int	ctd;
	int	ctd2;

	ctd = 0;
	ctd2 = 0;
	while (str[ctd] != '\n' && ctd < BUFFER_SIZE)
	{
		str[ctd] = '\0';
		ctd++;
	}
	if (str[ctd] == '\n')
	{
		str[ctd] = '\0';
		ctd++;
		while (ctd < BUFFER_SIZE)
		{
			str[ctd2] = str[ctd];
			str[ctd] = '\0';
			ctd++;
			ctd2++;
		}
	}
}

char	*get_next_line(int fd)
{
	static char		buffer [FOPEN_MAX][BUFFER_SIZE + 1];
	char			*str;
	int				ctd;

	ctd = 0;
	if (read(fd, 0, 0) < 0 || FOPEN_MAX <= fd || BUFFER_SIZE <= 0)
	{
		if (fd > 0 && FOPEN_MAX > fd)
			while (buffer[fd][ctd])
				buffer[fd][ctd++] = '\0';
		return (NULL);
	}
	str = NULL;
	while (buffer[fd][0] || read(fd, buffer[fd], BUFFER_SIZE) > 0)
	{
		str = ft_join_line(str, buffer[fd]);
		line_buffer_clean(buffer[fd]);
		if (str[ft_linelen(str) - 1] == '\n')
			return (str);
	}
	return (str);
}
