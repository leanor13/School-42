/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:11:03 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/30 19:13:31 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_param(char c, va_list args)
{
	if (c == '%')
		return (ft_putchar('%'));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 'i' || c == 'd')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if (c == 'u')
		return (ft_putnbr_u(va_arg(args, unsigned int)));
	else if (c == 'X' || c == 'x')
		return (ft_putnbr_hex(va_arg(args, int), c));
	else
	{
		write(1, "%%", 1);
		write(1, &c, 1);
		return (2);
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;

	if (!str)
		return (-1);
	len = 0;
	va_start(args, str);
	while (*str)
	{
		while (*str != '%' && *str)
		{
			ft_putchar_fd(*str, 1);
			len ++;
			str ++;
		}
		if (*str == '%')
		{
			if (!*(str + 1))
			{
				ft_putchar('%');
				len = -1;
			}
			else
			{
				len += ft_print_param(*(str + 1), args);
			}
			str += 2;
		}
	}
	va_end(args);
	return (len);
}

#include <stdio.h>
#include <limits.h>

int	main(void)
{
	//char	str[]="Hello";
	printf("%d\n", printf("%%"));
	//printf("%d\n", ft_printf("%y","Hi"));
	//ft_printf("ggg%c, sfd%sf%ifmdfl\n", 'N', "HELLO", 3428347);
	//printf("%d\n", ft_printf("ggg%c, sfd%sf%ifmdfl", 'N', "HELLO", 3428347));
	//printf("%d\n", printf("ggg%c, sfd%sf%ifmdfl", 'N', "HELLO", 3428347));
	//printf("%d\n", ft_printf("%u\n", 429400));
	//printf("%d\n", ft_printf(" %d %d %d %d %d %d %d", INT_MAX,
	//INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42));
	//printf("%d\n", printf(" %d %d %d %d %d %d %d", INT_MAX,
	//INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42));
	//printf("%d\n", printf("%i%s%l\n", 4535, "HellO", '!'));
}