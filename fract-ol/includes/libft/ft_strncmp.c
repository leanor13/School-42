/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:17:46 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/25 15:19:54 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	if (n == 0)
		return (0);
	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (-1);
	else if (!s2)
		return (1);
	while (*s1 == *s2 && *s1 != '\0' && n > 1)
	{
		s1 ++;
		s2 ++;
		n --;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}
