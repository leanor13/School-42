/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_custom.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:51:52 by leanor            #+#    #+#             */
/*   Updated: 2024/02/19 11:46:07 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	is_space(char c)
{
	return (c == 32 || (c > 8 && c < 14));
}

static int	is_sign(char c)
{
	return (c == 45 || c == 43);
}

int	ft_atoi_custom(const char *str)
{
	int		sign;
	long	number;

	while (is_space(*str))
		str++;
	sign = 1;
	if (is_sign(*str))
	{
		if (*str == '-')
			sign = sign * (-1);
		str++;
	}
	number = 0;
	while (ft_isdigit(*str))
	{
		number = 10 * number + (*str - '0');
		if ((number > INT_MAX && sign == 1) || (number > (long)INT_MAX + 1
				&& sign == -1))
			return (0);
		str++;
	}
	return (sign * number);
}
