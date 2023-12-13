#include <unistd.h>

int	char_in_str_e(char *s, char c, char end)
{
	int i = 0;

	while (s[i] && i < end)
	{
		if (s[i] == c)
			return (1);
		i ++;
	}
	return (0);
}

int	char_in_str(char *s, char c)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i ++;
	}
	return (0);
}

void	ft_union(char *str1, char *str2)
{
	int	i = 0;

	while (str1[i])
	{
		if (!char_in_str_e(str1, str1[i], i))
			write(1, &str1[i], 1);
		i ++;
	}
	i = 0;
	while (str2[i])
	{
		if (!char_in_str_e(str2, str2[i], i) && !char_in_str(str1, str2[i]))
			write(1, &str2[i], 1);
		i ++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 3)
		ft_union(av[1], av[2]);
	write(1, "\n", 1);
	return(0);
}