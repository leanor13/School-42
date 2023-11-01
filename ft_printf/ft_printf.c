/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:11:03 by yioffe            #+#    #+#             */
/*   Updated: 2023/11/01 11:20:51 by yioffe           ###   ########.fr       */
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
		if (*str != '%')
			len += ft_putchar(*str);
		else if (*str == '%')
		{
			if (*(str + 1) == '\0') 
				len += ft_putchar('%');
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

/* int	main(void)
{
	//char	str[]="Hello";
	printf("\noriginal length: %d\n", printf("%p", -1));
	printf("\nmy length: %d\n", ft_printf("%p", -1));
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
} */

/* int main() {

	
	int custom_printf_result, printf_result;
	char c = 'A';
	char *str = "Hello, World!";
	void *ptr = &c;
	int num = 42;
	int hexNum = 255;
	
	// Test %c
	
	custom_printf_result = ft_printf("%%c: %c\n", c);
	printf_result = printf("%%c: %c\n", c);
	if (custom_printf_result != printf_result) {
		printf("Custom ft_printf and printf return different values for %%c\n");
	}

	// Test %s
	
	custom_printf_result = ft_printf("%%s: %s\n", str);
	printf_result = printf("%%s: %s\n", str);
	if (custom_printf_result != printf_result) {
		printf("Custom ft_printf and printf return different values for %%s\n");
	}
	
	// Test %p
	
	custom_printf_result = ft_printf("%%p: %p\n", ptr);
	printf_result = printf("%%p: %p\n", ptr);
	printf("%d, %d\n", custom_printf_result, printf_result);
	if (custom_printf_result != printf_result) {
		printf("Custom ft_printf and printf return different values for %%p\n");
	}

	// Test %d and %i
	
	custom_printf_result = ft_printf("%%d: %d\n", num);
	printf_result = printf("%%d: %d\n", num);
	if (custom_printf_result != printf_result) {
		printf("Custom ft_printf and printf return different values for %%d\n");
	}
	
	custom_printf_result = ft_printf("%%i: %i\n", num);
	printf_result = printf("%%i: %i\n", num);
	if (custom_printf_result != printf_result) {
		printf("Custom ft_printf and printf return different values for %%i\n");
	}

	// Test %x and %X
	
	custom_printf_result = ft_printf("%%x: %x\n", hexNum);
	printf_result = printf("%%x: %x\n", hexNum);
	if (custom_printf_result != printf_result) {
		printf("Custom ft_printf and printf return different values for %%x\n");
	}
	
	custom_printf_result = ft_printf("%%X: %X\n", hexNum);
	printf_result = printf("%%X: %X\n", hexNum);
	if (custom_printf_result != printf_result) {
		printf("Custom ft_printf and printf return different values for %%X\n");
	}

	// Test %%
	
	custom_printf_result = ft_printf("%%%%: %%\n");
	printf_result = printf("%%%%: %%\n");
	if (custom_printf_result != printf_result) {
		printf("Custom ft_printf and printf return different values for %%\n");
	}
	// Test maximum and minimum values
	
	custom_printf_result = ft_printf("%%d: %d\n", INT_MAX);
	printf_result = printf("%%d: %d\n", INT_MAX);
	if (custom_printf_result != printf_result) {
		printf("Custom ft_printf and printf return different values for maximum value of %%d\n");
	}
	
	custom_printf_result = ft_printf("%%d: %d\n", INT_MIN);
	printf_result = printf("%%d: %d\n", INT_MIN);
	if (custom_printf_result != printf_result) {
		printf("Custom ft_printf and printf return different values for minimum value of %%d\n");
	}
	
	custom_printf_result = ft_printf("%%u: %u\n", UINT_MAX);
	printf_result = printf("%%u: %u\n", UINT_MAX);
	if (custom_printf_result != printf_result) {
		printf("Custom ft_printf and printf return different values for maximum value of %%u\n");
	}
	
	custom_printf_result = ft_printf("%%x: %x\n", UINT_MAX);
	printf_result = printf("%%x: %x\n", UINT_MAX);
	if (custom_printf_result != printf_result) {
		printf("Custom ft_printf and printf return different values for maximum value of %%x\n");
	}
	
	custom_printf_result = ft_printf("%%X: %X\n", UINT_MAX);
	printf_result = printf("%%X: %X\n", UINT_MAX);
	if (custom_printf_result != printf_result) {
		printf("Custom ft_printf and printf return different values for maximum value of %%X\n");
	}
	return 0;
} */