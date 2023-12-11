#include <stdlib.h>
#include <unistd.h>

int *ft_rrange(int start, int end)
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
        if (start <= end)
            res[i] = end - i;
        else
            res[i] = end + i;
        i ++;
    }
    return (res);
}

/* #include <stdio.h>

int main(void)
{
    int i = 0;
    int *range;

    range = ft_rrange(-1, 2);
    while (i < 4)
    {
        printf("%d, ", range[i]);
        i ++;
    }
    return (0);
} */