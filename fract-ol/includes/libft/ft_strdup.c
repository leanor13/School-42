/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:43:55 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/26 12:18:22 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char		*str_new;
	int			src_len;
	int			i;

	src_len = ft_strlen(src);
	str_new = (char *)malloc(src_len * sizeof(char) + 1);
	if (str_new == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		str_new[i] = src[i];
		i ++;
	}
	str_new[i] = '\0';
	return (str_new);
}
