/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:33:04 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/20 11:31:47 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_rec(int n, int len)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
		len ++;
	}
	if (n >= 10)
		len = (ft_putnbr_rec(n / 10, len));
	ft_putchar(n % 10 + '0');
	len ++;
	return (len);
}

int	ft_putnbr(int n)
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