#include <stdlib.h>
#include <stdio.h>

void    ft_prime_fact(int num)
{
    int fact;

    fact = 2;
    while (fact < num)
    {
        if (num % fact == 0)
        {
            num = num / fact;
            printf("%d*", fact);
        }
        else if (fact == 2)
            fact ++;
        else if (fact <= num / 2)
            fact += 2;
        else 
            break;
    }
    printf("%d", num);
}

int main(int ac, char **av)
{
    int num;

    if (ac == 2)
    {
        num = atoi(av[1]);
        if (num && num > 0)
            ft_prime_fact(atoi(av[1]));
    }
    printf("\n");
    return (0);
}