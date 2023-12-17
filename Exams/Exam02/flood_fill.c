

typedef struct  s_point
{
int           x;
int           y;
}               t_point;

void	flood_rec(char **tab, t_point size, t_point begin, char to_fill)
{
	if ((begin.x < 0) || (begin.y < 0) || 
			(begin.y >= size.y) || (begin.x >= size.x) || 
				(tab[begin.y][begin.x] != to_fill))
		return ;
	tab[begin.y][begin.x] = 'F';

	flood_rec(tab, size, (t_point){begin.x - 1, begin.y}, to_fill);
	flood_rec(tab, size, (t_point){begin.x + 1, begin.y}, to_fill);
	flood_rec(tab, size, (t_point){begin.x, begin.y - 1}, to_fill);
	flood_rec(tab, size, (t_point){begin.x, begin.y + 1}, to_fill);
}

void  flood_fill(char **tab, t_point size, t_point begin)
{
	char	to_fill;

	to_fill = tab[begin.y][begin.x];
	flood_rec(tab, size, begin, to_fill);
}

