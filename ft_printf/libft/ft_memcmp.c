/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:55:20 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/04 19:15:25 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_p;
	unsigned char	*s2_p;
	size_t			i;

	if (n == 0)
		return (0);
	s1_p = (unsigned char *)s1;
	s2_p = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_p[i] > s2_p[i])
			return (1);
		else if (s1_p[i] < s2_p[i])
			return (-1);
		i ++;
	}
	return (0);
}

/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	size_t			n = 4;
	char			s1[] = {0, 1, 2, 4, 4, 5};
	char			s2[] = {0, 1, 2, 3, 4, 5};

	printf("My fun result: %d\n", ft_memcmp(s1, s2, n));
	printf("Original fun result: %d\n", memcmp(s1, s2, n));
	printf("are they equal (1 if yes): %d", \
		ft_memcmp(s1, s2, n) == memcmp(s1, s2, n));
} */