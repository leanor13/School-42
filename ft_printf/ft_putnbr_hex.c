/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:20:35 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/20 10:56:13 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_hex_rec(unsigned int n, int len, char *hex_string)
{
	if (n >= 16)
		len = (ft_putnbr_hex_rec(n / 16, len, hex_string));
	len += ft_putchar(hex_string[n % 16]);
	return (len);
}

int	ft_putnbr_hex(int n, char c)
{
	int		len;

	len = 0;
	if (c == 'x')
		len += ft_putnbr_hex_rec((unsigned int) n, len, "0123456789abcdef");
	else if (c == 'X')
		len += ft_putnbr_hex_rec((unsigned int) n, len, "0123456789ABCDEF");
	return (len);
}

/* int	main(void)
{
	ft_putnbr_hex(15, 'x');
	return (0);
}
 */