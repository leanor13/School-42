/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:16:35 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/25 15:20:18 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (-1);
	else if (!s2)
		return (1);
	while (*s1 == *s2 && *s1 != '\0')
	{
		s1 ++;
		s2 ++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}
