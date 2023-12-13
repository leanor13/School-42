#include <stdlib.h>
#include <unistd.h>

int *ft_range(int start, int end)
{
    int size;
    int *res;
    int i = 0;

    if (start > end)
        size = start - end + 1;
    else
        size = end - start + 1;
    res = malloc(sizeof(int) * size);
    if (!res)
        return (NULL);
    while (i <= size - 1)
    {
        if (start >= end)
            res[i] = start - i;
        else
            res[i] = start + i;
        i ++;
    }
    return (res);
}

/* #include <stdio.h>

int main(void)
{
    int i = 0;
    int *range;

    range = ft_range(0, -3);
    while (i < 4)
    {
        printf("%d, ", range[i]);
        i ++;
    }
    return (0);
} */