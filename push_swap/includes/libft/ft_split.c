/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:50:22 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/10 11:16:22 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	res;

	res = 0;
	while (*s)
	{
		while (*s == c)
			s ++;
		if (*s)
		{
			res ++;
			while (*s && *s != c)
				s ++;
		}
	}
	return (res);
}

static char	*allocate_word(char const *s, char c)
{
	char	*word;
	int		len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = ft_substr(s, 0, len);
	return (word);
}

static void	free_res(char **result, int i)
{
	while (i > 0)
		free(result[--i]);
	free(result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		count;
	int		i;

	count = ft_count_words(s, c);
	result = (char **)malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < count)
	{
		while (*s == c)
			s++;
		result[i] = allocate_word(s, c);
		if (!result[i])
		{
			free_res(result, i);
			return (NULL);
		}
		while (*s && *s != c)
			s++;
		i++;
	}
	result[i] = NULL;
	return (result);
}

/* #include <stdio.h>

int	main(void)
{
	char	s[]="";
	char	c = 'd';
	char	**res;
	int		i = 0;

	res = ft_split(s, c);
	while (res[i])
	{
		printf("%d: %s\n", i, res[i]);
		free(res[i]);
		i ++;
	}
	free(res);
} */