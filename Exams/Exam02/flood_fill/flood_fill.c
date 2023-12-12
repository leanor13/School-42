
typedef struct  s_point
{
	int           x;
	int           y;
}               t_point;

void	fill(char **tab, t_point size, t_point curr, char to_fill)
{
	if (curr.x >= size.x || curr.y >= size.y || curr.x < 0 || curr.y < 0 || (tab[curr.y][curr.x] != to_fill))
		return ;
	tab[curr.y][curr.x] = 'F';
	fill(tab, size, (t_point){curr.x - 1, curr.y}, to_fill);
	fill(tab, size, (t_point){curr.x + 1, curr.y}, to_fill);
	fill(tab, size, (t_point){curr.x, curr.y - 1}, to_fill);
	fill(tab, size, (t_point){curr.x, curr.y + 1}, to_fill);
}

void  flood_fill(char **tab, t_point size, t_point begin)
{
	fill(tab, size, begin, tab[begin.y][begin.x]);	
}