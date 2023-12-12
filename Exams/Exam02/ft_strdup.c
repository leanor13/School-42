
#include <stdlib.h>

int	ft_strlen(char *str)
{
    int len = 0;
    
    while (str[len])
        len ++;
    return (len);
}

char    *ft_strdup(char *src)
{
    int     len;
    char    *res;
    int     i = 0;

    len = ft_strlen(src);
    res = malloc(sizeof(char) * (len + 1));
    if (!res)
        return (NULL);
    while (i < len)
    {
        res[i] = src[i];
        i ++;
    }
    res[i] = '\0';
    return (res);
}