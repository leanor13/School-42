
#include <stdio.h>
#include <stdlib.h>

void	ft_pgcd(char *s1, char *s2)
{
	int	n1;
	int	n2;
	int	min;
	int	i;

	n1 = atoi(s1);
	n2 = atoi(s2);
	if (n1 <= 0 || n2 <= 0)
		return ;
	if ((n1 - n2) > 0)
		min = n2;
	else
		min = n1;
	i = min;
	while (i > 0)
	{
		if (n1 % i == 0 && n2 % i == 0)
		{
			printf("%d", i);
			return ;
		}
		i --;
	}
}

int	main(int ac, char **av)
{
	if (ac == 3)
		ft_pgcd(av[1], av[2]);
	printf("\n");
}