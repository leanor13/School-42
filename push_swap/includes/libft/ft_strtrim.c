/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:00:48 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/05 18:47:40 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_str(const char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str ++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;
	size_t	res_len;
	char	*res;

	begin = 0;
	end = ft_strlen(s1) - 1;
	while (s1[begin] && char_in_str(set, s1[begin]))
		begin ++;
	if (!s1[begin])
		return (ft_strdup(""));
	while (s1[end] && char_in_str(set, s1[end]))
		end --;
	res_len = end - begin + 1;
	res = (char *)malloc(res_len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1 + begin, res_len + 1);
	return (res);
}
/* 
#include <stdio.h>

int	main(void)
{
	char	s1[] = "ddsfasfsasfasfsdgsdg";
	char	set[] = "d";
	char	*res;

	res = ft_strtrim(s1, set);
	printf("Original: %s, trimmed: %s", s1, res);
	free(res);
	return (0);
} */