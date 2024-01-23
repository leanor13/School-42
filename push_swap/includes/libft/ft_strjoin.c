/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:49:09 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/05 12:40:42 by yioffe           ###   ########.fr       */
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

/* #include <stdio.h>
int	main(void)
{
	char	str1[] = "hey";
	char	str2[] = "is it a   ";
	char	*res;

	res = ft_strjoin(str1, str2);
	printf("str1: %s\nstr2: %s\nresult: %s\n", str1, str2, res);
	free(res);
} */
