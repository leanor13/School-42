/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:54:52 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/05 18:37:30 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_length;

	src_length = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (src_length);
	i = 0;
	while (i < (size - 1) && src[i] != '\0')
	{
		dest[i] = src[i];
		i ++;
	}
	dest[i] = '\0';
	return (src_length);
}

/* #include <stdio.h>

int	main(void)
{
	char	source[] = "source";
	char	destination[] = "Hi I am dest";
	unsigned int	n;
	
	n = 5;
	n = ft_strlcpy(destination, source, 0);
	printf("Source:\n%s\n", source);
	printf("New Destination:%s \nsource length: %d\n", destination, n);
	return 0;
}
 */
