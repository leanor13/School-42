
#include <unistd.h>
#include <stdio.h>

void	ft_putnum(int num)
{
	char	c;

	if (num >= 10)
	{
		ft_putnum(num / 10);
		ft_putnum(num % 10);
	}
	else
	{
		c = num + '0';
		write(1, &c, 1);
	}
}

int		ft_atoi(char *str)
{
	int	res = 0;

	while (*str)
	{
		if (*str < '0' || *str > '9')
			return(0);
		res = res * 10 + (*str - '0');
		str ++;
	}
	return (res);
}

int	ft_is_prime(int num)
{
	int i = 3;

	if (num <= 1)
		return (0);
	if (num == 2)
		return (1);
	if (num % 2 == 0)
		return (0);
	while (i < num / 2)
	{
		if (num % i == 0)
			return (0);
		i += 2;
	}
	return (1);
}

int		prime_sum(int num)
{
	int	res = 0;
	int	i = 2;

	if (num <= 1)
		return (0);
	while (i <= num)
	{
		if (ft_is_prime(i) == 1)
			res += i;
		i ++;
	}
	return (res);
}

int	main(int ac, char **av)
{
	int	num;

	if (ac == 2)
	{
		num = (ft_atoi(av[1]));
		if (num > 1)
			ft_putnum(prime_sum(num));
	}
	else
		write(1, "0", 1);
	write(1, "\n", 1);
	return (0);
}