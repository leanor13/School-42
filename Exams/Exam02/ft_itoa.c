
#include <stdlib.h>

int	count_digits(int num)
{
	int	dig = 1;
	if (num == -2147483648)
		return (11);
	if (num < 0)
	{
		dig ++;
		num *= -1;
	}
	while (num >= 10)
	{
		dig ++;
		num = num / 10;
	}
	return (dig);
}

char	*ft_itoa(int nbr)
{
	char	*res;
	int		len;
	long int	num;

	num = nbr;
	len = count_digits(num);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	len --;
	if (num == 0)
	{
		res[0] = '0';
		return (res);
	}
	if (num < 0)
	{
		res[0] = '-';
		num *= -1;
	}
	while (num > 0)
	{
		res[len] = num % 10 + '0';
		num = num / 10;
		len --;
	}
	return (res);
}

/* #include <stdio.h>

int	main(void)
{
	printf("9: %s\n", ft_itoa(9));
	printf("1657: %s\n", ft_itoa(1657));
	printf("-1: %s\n", ft_itoa(-1));
	printf("-2147483648: %s\n", ft_itoa(-2147483648));
	printf("-100: %s\n", ft_itoa(-100));
	printf("10: %s\n", ft_itoa(10));
	printf("11: %s\n", ft_itoa(11));
} */