/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:52:11 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/26 12:14:38 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

static int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len ++;
	return (len);
}

int	ft_putstr(char *s)
{
	if (!s)
		return (ft_putstr("(null)"));
	return (write(1, s, ft_strlen(s)));
}

static int	ft_putnbr_base_rec(size_t n, int len, char *base)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if (n >= base_len)
		len = (ft_putnbr_base_rec(n / base_len, len, base));
	len += ft_putchar(base[n % base_len]);
	return (len);
}

int	ft_nbr(long long int n, char *base, char type)
{
	int		len;

	len = 0;
	if (type == 'p')
	{
		if (n == 0)
			return (ft_putstr("(nil)"));
		len += ft_putstr("0x");
		len += ft_nbr((unsigned long int) n, base, 'u');
	}
	else if (type == 'u')
		len += ft_putnbr_base_rec(n, len, base);
	else if (type == 'i')
	{
		if (n == -2147483648)
			return (ft_putstr("-2147483648"));
		if (n < 0)
		{
			ft_putchar('-');
			n *= -1;
			len ++;
		}
		len += ft_nbr((int) n, base, 'u');
	}
	return (len);
}
