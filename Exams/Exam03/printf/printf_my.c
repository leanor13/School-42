#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

void	ft_putstr(char *s, int *len)
{
	if (!s)
	{
		*len += write(1, "(null)", 6);
		return ;
	}
	while (*s)
	{
		*len += write(1, s, 1);
		s ++;
	}
}

void	hex_digit(long long int num, int base, int *len)
{
	if (num < 0)
	{
		len += write(1, "-", 1);
		num = -1 * num;
	}
	if (num >= base)
	{
		hex_digit(num / base, base, len);
	}
	*len = write(1, &"0123456789abcdef"[num % base], 1);
}

int ft_printf(const char *str, ... )
{
	va_list	pointer;
	int	len;

	len = 0;
	va_start(pointer, str);
	while (*str)
	{
		if (*str == '%' && *(str+1) != '\0')
		{
			str ++;
			if (*str=='s')
				ft_putstr(va_arg(pointer, char *), &len);
			else if (*str == 'd')
				hex_digit((long long int)va_arg(pointer, int), 10, &len);
			else if (*str == 'x')
				hex_digit((long long int)va_arg(pointer, unsigned int), 16, &len);
		}
		else
			len += write(1, str, 1);
		str ++;
	}
	va_end(pointer);
	return (len);
}

// int	main(void)
// {
// 	char	s[]="Hello";
// 	int		len;

// 	len = ft_printf("Hi %s", s);
// 	printf("length: %d", len);
// 	return (0);
// }

int main(void)
{
    int num = 42;
    char *str = "ola mundio";
    int hex = 42;

    printf("printf: \n");
    printf("num: %d\nstr: %s\nhex: %x\n", num, str, hex);
    printf("ft_printf: \n");
    ft_printf("num: %d\nstr: %s\nhex: %x\n", num, str, hex);
    return (0);
}