/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:35:09 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/23 15:41:36 by yioffe           ###   ########.fr       */
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

static int	handle_spaces(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i ++;
	if (is_sign(str[i]))
	{
		if (str[i] == '-')
			*sign = -1;
		i ++;
	}
	return (i);
}

double	ft_atof(char *str)
{
	int			sign;
	double		number;
	double		shift;

	sign = 1;
	number = 0.0;
	shift = 0.1;
	str += handle_spaces(str, &sign);
	while (ft_isdigit(*str))
	{
		number = 10 * number + (*str - '0');
		str ++;
	}
	if (*str == '.')
	{
		str ++;
		while (ft_isdigit(*str))
		{
			number = number + (*str - '0') * shift;
			shift *= 0.1;
			str ++;
		}
	}
	return (sign * number);
}

/* #include <float.h>

int	main(void)
{
	char	s[]="  6558.6  ";

	printf("Minimum value for double: %e\n", DBL_MIN);
    printf("Maximum value for double: %e\n", DBL_MAX);
	printf("string: %s, number: %f", s, ft_atof(s));
	return 0;
} */