
#include <unistd.h>

void    ft_is_hidden(char *s1, char *s2)
{
    while (*s2)
    {
        if (*s1 == *s2)
            s1 ++;
        s2 ++;
    }
    if (*s1 == '\0')
        write(1, "1", 1);
    else
        write(1, "0", 1);
}

int     main(int ac, char **av)
{    
    if (ac == 3)
    {
        ft_is_hidden(av[1], av[2]);
    }
    write(1, "\n", 1);
    return (0);
}