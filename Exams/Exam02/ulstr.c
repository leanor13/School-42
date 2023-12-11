
#include <unistd.h>

int main(int ac, char **av)
{
    char *str;
    char c;
    
    if (ac == 2)
    {
        str = av[1];
        while (*str)
        {
            if (*str >= 'a' && *str <= 'z')
                c = *str - 32;
            else if (*str >= 'A' && *str <= 'Z')
                c = *str + 32;
            else
                c = *str;
            write(1, &c, 1);
            str ++;
        }
    }
    write(1, "\n", 1);
    return (0);
}