
#include "../includes/push_swap.h"

static void	ft_pt_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	arr_qsort(int *arr, int len)
{
	int	pivot;
	int	i;
	int	j;

	if (len < 2)
		return ;
	pivot = arr[len / 2];
	i = 0;
	j = len - 1;
	while (1)
	{
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i >= j)
			break ;
		ft_pt_swap(&arr[i], &arr[j]);
		i++;
		j--;
	}
	arr_qsort(arr, i);
	arr_qsort(arr + i, len - i);
}
int	ft_med_count(t_dlist *lst, int len)
{
	int	*indexes;
	int	i;
	int	med;

	indexes = malloc(sizeof(int) * len);
	if (!indexes)
		return (0);
	i = 0;
	while (i < len && lst)
	{
		indexes[i] = lst->n_cont;
		lst = lst->next;
		i++;
	}
	arr_qsort(indexes, len);
	med = indexes[len / 2];
	return (free(indexes), med);
}
