/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:36:31 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/26 12:18:18 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s[0] == '\0' && (char) c == '\0')
		return ((char *) s);
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i ++;
		if ((char) c == '\0' && s[i] == '\0')
			return ((char *)(s + i));
	}
	return (NULL);
}
