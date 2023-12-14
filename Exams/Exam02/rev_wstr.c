
#include <stdlib.h>
#include <unistd.h>

int	is_space(char c)
{
	return (c == 32 || (c > 8 && c < 15) || c == 0);
}

char **ft_split(char *s)
{
	char **res;
	int	len = 0;
	int	i = 0;

	while (s[len])
		len ++;
	res = malloc(sizeof(char *) * len);
	if (!res)
		return (NULL);
	while (*s)
	{
		if (!is_space(*s))
		{
			res[i] = s;
			i ++;
		}
		while (!is_space(*s))
			s ++;
		if (*s && is_space(*s))
			s ++;
	}
	res[i] = NULL;
	return (res);
}

void	rev_print(char *str)
{
	char **spli;
	int i = 0;
	int	j = 0;
	char	c;

	spli = ft_split(str);
	while (spli[i])
		i ++;
	i --;
	while(i > 0)
	{
		j = 0;
		while (spli[i][j] && !is_space(spli[i][j]))
		{
			c = spli[i][j];
			write(1, &c, 1);
			j ++;
		}
		write(1, " ", 1);
		i --;
	}
	if (i == 0)
	{
		j = 0;
		while (spli[i][j] && !is_space(spli[i][j]))
		{
			c = spli[i][j];
			write(1, &c, 1);
			j ++;
		}
	}
	free(spli);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		rev_print(av[1]);
	write(1, "\n", 1);
	return (0);
}