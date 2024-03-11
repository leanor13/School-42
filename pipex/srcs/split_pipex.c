/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:19:55 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/11 13:59:15 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*skip_word(char *s, char c)
{
	char	q;

	while (*s == c)
		s++;
	if (is_quote(*s))
	{
		q = *s;
		s++;
		while (*s && *s != q)
		{
			if (is_quote(*s))
				return (ft_putstr_fd(ERR_NESTED_QUOTES, STDERR_FILENO),
					(char *) NEG_ERROR);
			s ++;
		}
		if (*s == q)
			s++;
		else
			return (ft_putstr_fd(ERR_SINGLE_QUOTE, STDERR_FILENO),
				(char *) NEG_ERROR);
	}
	else
		while (*s && *s != c)
			s++;
	return (s);
}

static int	ft_count_words(char *s, char c)
{
	int		res;

	res = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			res++;
			s = skip_word(s, c);
			if (s == (char *) NEG_ERROR)
				return (NEG_ERROR);
		}
	}
	return (res);
}

static char	*allocate_word(char *s, char c)
{
	char	*word;
	int		len;
	char	q;

	len = 0;
	if (is_quote(s[len]))
	{
		q = *s;
		s++;
		while (s[len] && s[len] != q)
			len++;
	}
	else
		while (s[len] && (s[len] != c))
			len++;
	word = ft_substr(s, 0, len);
	if (!word)
	{
		perror("Failed split word memory allocation");
		return (NULL);
	}
	return (word);
}

static void	free_res(char **result, int i)
{
	while (i > 0)
		free(result[--i]);
	free(result);
}

char	**ft_split_pipex(char *s, char c)
{
	char	**result;
	int		count;
	int		i;

	count = ft_count_words(s, c);
	if (count == NEG_ERROR)
		return (NULL);
	result = (char **)malloc((count + 1) * sizeof(char *));
	if (!result)
		return (perror("Failed split memory allocation"), NULL);
	i = 0;
	while (i < count)
	{
		while (*s == c)
			s++;
		result[i] = allocate_word(s, c);
		if (!result[i])
			return (free_res(result, i), NULL);
		s = skip_word(s, c);
		i++;
	}
	result[i] = NULL;
	return (result);
}
