/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:36:31 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/04 14:15:11 by yioffe           ###   ########.fr       */
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

/* #include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	printf("My result: %s\n", ft_strchr("mytest", 357));
	printf("Real result: %s\n", strchr("mytest", 357));
	printf("My result: %s\n", ft_strchr("mytest", 1024));
	printf("Real result: %s\n", strchr("mytest", 1024));
	if (argc != 3)
		return (0);
	printf("My result: %s\n", ft_strchr(argv[1], *argv[2]));
	printf("Real result: %s\n", strchr(argv[1], *argv[2]));
	return (0);
} */