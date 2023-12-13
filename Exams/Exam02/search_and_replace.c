
#include <unistd.h>

void	repl(char *str, char a, char b)
{
	while (*str)
	{
		if (*str != a)
			write(1, str, 1);
		else
			write(1, &b, 1);
		str ++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 4 && av[2][1] == '\0' && av[3][1] == '\0')
		repl(av[1], av[2][0], av[3][0]);
	write(1, "\n", 1);
}