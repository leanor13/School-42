
#include <unistd.h>

int	is_space(char c)
{
	return (c == 32 || (c > 8 && c < 15));
}

int	ft_putstr(char *s)
{
	int	i = 0;
	int	j;
	int	run = 0;

	while (is_space(s[i]))
		i ++;
	j = i;
	while (s[j])
		j ++;
	while (is_space(s[j - 1]))
		j --;
	j --;
	while (i <= j)
	{
		while (!is_space(s[i]) && i <= j && s[i])
		{
			write(1, &s[i], 1);
			i ++;
			run = 1;
		}
		if (i < j)
			write(1, " ", 1);
		while (is_space(s[i]) && s[i])
			i ++;
	}
	return (run);
}

void	rostr(char *s)
{
	int	i = 0;
	int end_f;
	int beg_f;

	while (s[i] && is_space(s[i]))
		i ++;
	beg_f = i;
	while (s[i] && !is_space(s[i]))
		i ++;
	end_f = i;
	if (ft_putstr(s + end_f))
		write(1, " ", 1);
	write(1, &s[beg_f], end_f - beg_f);
}

int	main(int ac, char **av)
{
	if (ac >= 2)
		rostr(av[1]);
	write(1, "\n", 1);
	return (0);
}