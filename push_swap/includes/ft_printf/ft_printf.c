/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:11:03 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/31 15:27:10 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_param(char c, va_list args)
{
	if (!c)
		return (0);
	if (c == '%')
		return (ft_putchar('%'));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 'i' || c == 'd')
		return (ft_nbr(va_arg(args, int), DEC, 'i'));
	else if (c == 'p')
		return (ft_nbr((unsigned long int) va_arg(args, void *), HEX_LOW, 'p'));
	else if (c == 'u')
		return (ft_nbr(va_arg(args, unsigned int), DEC, 'u'));
	else if (c == 'X')
		return (ft_nbr(va_arg(args, unsigned int), HEX_UP, 'u'));
	else if (c == 'x')
		return (ft_nbr(va_arg(args, unsigned int), HEX_LOW, 'u'));
	else
		return (ft_putchar('%') + ft_putchar(c));
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
		if (*str != '%')
			len += ft_putchar(*str);
		else if (*str == '%')
		{
			if (*(str + 1) == '\0')
				len = -1;
			else
			{
				len += ft_print_param(*(str + 1), args);
				str ++;
			}
		}
		str ++;
	}
	va_end(args);
	return (len);
}
