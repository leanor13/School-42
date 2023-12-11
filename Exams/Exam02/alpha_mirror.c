#include <unistd.h>

void    ft_mirror(char *str)
{
    char    c;

    while(*str)
    {
        if (*str >= 'A' && *str <= 'Z')
            c = *str + 25 - (25 - (90 - *str))*2;
        else if (*str >= 'a' && *str <= 'z')
            c = *str + 25 - (25 - (122 - *str))*2;
        else
            c = *str;
        write(1, &c, 1);
        str ++;
    }
}

int main(int ac, char **av)
{    
    if (ac == 2)
    {
        ft_mirror(av[1]);
    }
    write(1, "\n", 1);
    return (0);
}