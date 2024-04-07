/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_custom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:03:23 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/07 15:58:40 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_space(char c)
{
	return (c == 32 || (c > 8 && c < 14));
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	atoi_positive(char *str)
{
	int		number;

	if (!str || !*str)
		return (NEG_ERROR);
	while (is_space(*str))
		str ++;
	number = 0;
	while (is_digit(*str))
	{
		number = 10 * number + (*str - '0');
		str ++;
	}
	if (*str != '\0')
		return (NEG_ERROR);
	return (number);
}

