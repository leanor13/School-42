
int	    is_power_of_2(unsigned int n)
{
	if (n == 1)
		return (1);
	if (n == 0)
		return (0);
	while (n > 1)
	{
		if (n % 2 == 1)
			return (0);
		n = n / 2;
	}
	return (1);
}

/* #include <stdio.h>

int	main(void)
{
	printf("16: %d\n", is_power_of_2(16));
	printf("0: %d\n", is_power_of_2(2147483647));
	printf("7: %d\n", is_power_of_2(7));
} */