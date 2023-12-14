
#include <unistd.h>

char	rot_13(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		if (c + 13 <= 'Z')
			c = c + 13;
		else
			c = 'A' + c + 12 - 'Z';
	}
	if (c >= 'a' && c <= 'z')
	{
		if (c + 13 <= 'z')
			c = c + 13;
		else
			c = 'a' + c + 12 - 'z';
	}
	return (c);
}

void	rot_str(char *s)
{
	char	c;

	while (*s)
	{
		c = rot_13(*s);
		write(1, &c, 1);
		s ++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		rot_str(av[1]);
	write(1, "\n", 1);
	return (0);
}