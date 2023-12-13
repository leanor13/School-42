
int		max(int *tab, unsigned int len)
{
	int	max = -2147483648;
	int i = 0;

	if (len == 0 || !tab)
		return (0);
	while (i < len)
	{
		if (tab[i] > max)
			max = tab[i];
		i ++;
	}
	return (max);
}