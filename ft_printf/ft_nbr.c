/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:08:55 by yioffe            #+#    #+#             */
/*   Updated: 2023/11/01 13:33:45 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		len += ft_nbr((unsigned long int) n, HEX_LOW, 'u');
	}
	else
		len += ft_putnbr_base_rec(n, len, base);
	return (len);
}

/* int	main(void)
{
	ft_putnbr_hex(15, 'x');
	return (0);
}
 */