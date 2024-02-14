
#include "../includes/push_swap.h"

static void	ft_pt_swap(int *a, int *b)
{
    int	temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

static int	partition(int *arr, int low, int high)
{
    int	pivot;
    int	i;
    int	j;

    pivot = arr[high];
    i = low - 1;
    j = low;
    while (j <= high - 1)
    {
        if (arr[j] <= pivot)
        {
            i++;
            ft_pt_swap(&arr[i], &arr[j]);
        }
        j++;
    }
    ft_pt_swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void	arr_qsort(int *arr, int low, int high)
{
    int	pi;

    if (low < high)
    {
        pi = partition(arr, low, high);
        arr_qsort(arr, low, pi - 1);
        arr_qsort(arr, pi + 1, high);
    }
}