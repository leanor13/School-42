/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:25:51 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/20 11:19:03 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(void *ptr)
{
	unsigned long long int	addr;
	char					hex_string[24];
	int						i;

	if (!ptr)
		return (ft_putstr("(nil)"));
	addr = (unsigned long long int)ptr;
	i = sizeof(unsigned long long int) * 2 + 2;
	hex_string[i] = '\0';
	i--;
	while (addr > 0 && i >= 2)
	{
		hex_string[i] = "0123456789abcdef"[addr & 0xf];
		addr >>= 4;
		i--;
	}
	hex_string[i - 1] = '0';
	hex_string[i] = 'x';
	return (ft_putstr(hex_string + i - 1));
}

/* int main() {
	int value = 42;
	int *ptr = &value;

	ft_putptr(ptr);
	write(1, "\n", 1);
	return 0;
} */