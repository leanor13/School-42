/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:49:09 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/26 12:18:30 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *dest, char const *src)
{
	char	*result;
	char	*start_ptr;
	int		total_size;

	total_size = ft_strlen(dest) + ft_strlen(src);
	result = (char *)malloc(total_size + 1);
	if (result == NULL)
		return (NULL);
	start_ptr = result;
	while (*dest != '\0')
	{
		*result = *dest;
		result ++;
		dest ++;
	}
	while (*src != '\0')
	{
		*result = *src;
		result ++;
		src ++;
	}
	*result = '\0';
	return (start_ptr);
}
