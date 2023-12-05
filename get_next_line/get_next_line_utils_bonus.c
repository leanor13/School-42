/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:26:00 by yioffe            #+#    #+#             */
/*   Updated: 2023/12/05 12:39:21 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
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

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n--)
		*ptr++ = '\0';
}
