
#include <unistd.h>

int simple_atoi(char *s)
{
    int num = 0;

    while (*s == '+')
        s ++;
    while (*s)
    {
        num = num * 10 + (*s - '0');
        s ++;
    }
    return (num);
}

void putnbr(int  nbr)
{
    char    c;
    if (nbr >= 10)
        putnbr(nbr / 10);
    c = (nbr % 10) + '0';
    write(1, &c, 1);
}

void mul_wr(void)
{
    write(1, " x ", 3);
}

void eq_wr(void)
{
    write(1, " = ", 3);
}

void    mult(int num)
{
    int i = 1;

    if (num > 2147483647 / 9)
        return;
    while (i < 10)
    {
        putnbr(i);
        mul_wr();
        putnbr(num);
        eq_wr();
        putnbr(num * i);
        write(1, "\n", 1);
        i ++;
    }
}

int main(int ac, char **av)
{
    if (ac == 2 && av[1][0] != '-')
        mult(simple_atoi(av[1]));
        //putnbr(108);
    else
        write(1, "\n", 1);
    return (0);
}