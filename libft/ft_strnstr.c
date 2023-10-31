/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:23:56 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/04 19:37:52 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		while ((big[i + j] == little[j]) && big[i + j] != '\0' && i + j < len)
			j ++;
		if (little[j] == '\0')
			return ((char *)(big + i));
		i ++;
		j = 0;
	}
	return (NULL);
}

/* //#include <string.h>
#include <stdio.h>

int	main(void)
{
	char	to_find[] = "needle";
	char	str1[] = "this is the neele for sewingneed";
	char	str2[] = "this is the needle";
	size_t	n = 15;

	printf("original: %s\nanswer: %s\n", str1, ft_strnstr(str1, to_find, n));
	//printf("original: %s\nanswer: %s\n", str1, strnstr(str1, to_find, n));
	printf("original: %s\nanswer: %s\n", str2, ft_strnstr(str2, to_find, n));
	//printf("original: %s\nanswer: %s\n", str2, strnstr(str2, to_find, n));

} */
