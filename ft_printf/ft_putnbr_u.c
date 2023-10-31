/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:33:04 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/20 11:22:28 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_rec(unsigned int n, int len)
{
	if (n >= 10)
		len = (ft_putnbr_rec(n / 10, len));
	ft_putchar(n % 10 + '0');
	len ++;
	return (len);
}

int	ft_putnbr_u(unsigned int n)
{
	int	len;

	len = 0;
	len = ft_putnbr_rec(n, len);
	return (len);
}

/* #include <stdio.h>

int	main(void)
{
	printf("\nlength: %d\n", ft_putnbr(-34234));
	return (0);
} */