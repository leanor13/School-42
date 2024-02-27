/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:19:55 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/27 13:41:50 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static int	ft_count_words(char const *s, char c)
{
	int		res;
	char	q;

	res = 0;
	while (*s)
	{
		while (*s == c)
			s ++;
		if (is_quote(*s))
		{
			q = *s;
			res ++;
			while (*s && *s != q)
				s ++;
		}
		else if (*s)
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
	char	q;

	len = 0;
	if (is_quote(s[len]))
	{
		q = *s;
		s ++;
		while (s[len] && s[len] != q)
			len++;
		len --;
	}
	else
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

char	**ft_split_pipex(char const *s, char c)
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
	//ft_printf("split");
	return (result);
}
