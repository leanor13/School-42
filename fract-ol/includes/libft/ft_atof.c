/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:35:09 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/23 14:07:12 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	return (c == 32 || (c > 8 && c < 14));
}

static int	is_sign(char c)
{
	return (c == 45 || c == 43);
}

double	ft_atof(const char *str)
{
	int			sign;
	double		number;
	double		num_dec;
	int			divisor;

	while (is_space(*str))
		str ++;
	sign = 1;
	if (is_sign(*str))
	{
		if (*str == '-')
			sign = sign * (-1);
		str ++;
	}
	number = 0;
	num_dec = 0;
	while (ft_isdigit(*str))
	{
		number = 10 * number + (*str - '0');
		str ++;
	}
	if (*str == '.')
	{
		str ++;
		divisor = 1;
		while (ft_isdigit(*str))
		{
			num_dec = num_dec * 10 + (*str - '0');
			divisor *= 10;
			str ++;
		}
	}
	return (sign * (number + num_dec/divisor));
}

int	main(void)
{
	char	s[]="  -1.0187  ";

	printf("string: %s, number: %f", s, ft_atof(s));
	return 0;
}