/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:40:21 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/04 19:15:49 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_ptr;
	unsigned char	ch;
	size_t			i;

	s_ptr = (unsigned char *)s;
	ch = (unsigned char)c;
	i = 0;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if ((unsigned char)s_ptr[i] == ch)
			return (s_ptr + i);
		i ++;
		if (ch == '\0' && i < n && (unsigned char)s_ptr[i] == '\0')
			return (s_ptr + i);
	}
	return (NULL);
}

/* #include <string.h>
#include <stdio.h>

int	main(void)
{	
	void			*s1_ptr;
	int				c = 2;
	char	s1[] = {0, 1, 2 ,3 ,4 ,5};
	int				n = 3;

	s1_ptr = s1;
	printf("My fun result: %p\n", ft_memchr(s1, c, n));
	printf("Original fun result: %p\n", memchr(s1, c, n));
	printf("are they equal (1 if yes): %d", \
		ft_memchr(s1, c, n) == memchr(s1, c, n));
} */