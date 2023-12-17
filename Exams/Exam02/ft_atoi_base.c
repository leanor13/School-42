
char	to_low(char c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}

int	base_to_int(char cha, int b)
{
	char	base[] ="0123456789abcdef";
	int		i = 0;
	char	c;

	c = to_low(cha);
	while (base[i] && i < b)
	{
		if (c == base[i])
			return (i);
		i ++;
 	}
	return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	long int	res = 0;
	int	i = 0;
	int curr;

	if (str[i] == '+' || str[i] == '-')
		i ++;
	while (str[i])
	{	
		curr = base_to_int(str[i], str_base);
		if (curr >= 0)
			res = res * str_base + curr;
		else
			break;
		i ++;
	}
	if (str[0] == '-')
		res *= -1;
	return (res);
}

/* #include <stdio.h>

int	main(int ac, char **av)
{
	if (ac == 2)
		printf("Base 8 - Converted to int: %d\n", ft_atoi_base(av[1], 8));
	return (0);
}
 */
