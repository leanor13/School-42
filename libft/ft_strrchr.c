/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:15:37 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/04 17:35:21 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if ((char) c == '\0')
		return ((char *)(s + i));
	i --;
	while (i >= 0)
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i --;
	}
	return (NULL);
}

/* #include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	printf("My result: %s\n", ft_strrchr("mytest", 357));
	printf("Real result: %s\n", strrchr("mytest", 357));
	printf("My result: %s\n", ft_strrchr("mytest", 1024));
	printf("Real result: %s\n", strrchr("mytest", 1024));
	if (argc != 3)
		return (0);
	printf("My result: %s\n", ft_strrchr(argv[1], *argv[2]));
	printf("Real result: %s\n", strrchr(argv[1], *argv[2]));
	return (0);
} */