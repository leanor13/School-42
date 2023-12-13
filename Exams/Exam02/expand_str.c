
#include <unistd.h>

int	is_space(char c)
{
	return (c == 32 || (c > 8 && c < 15) || c == 0);
}

void	expand(char *str)
{
	int	i = 0;
	int j = 0;
	
	while (str[j])
		j ++;
	while(str[j - 1] && is_space(str[j - 1]))
		j --;
	while (i < j)
	{
		while (str[i] && is_space(str[i]))
			i ++;
		while (str[i] && !is_space(str[i]))
		{
			write(1, &str[i], 1);
			i ++;
		}
		if (i < j)
			write(1, "   ", 3);
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		expand(av[1]);
	write(1, "\n", 1);
	return (0);
}