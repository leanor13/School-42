#include <unistd.h>

int is_space(char c)
{
    return ((c > 8 && c < 15) || c == 32);
}

void ft_print(char *s)
{
    int start = 0;
    int end;
    int    i;
    
    end = 0;
    while (s[end + 1])
        end ++;
    start = 0;
    while (is_space(s[start]) && s[start])
        start ++;
    while (is_space(s[end]))
        end --;
    i = start;
    while (i <= end)
    {
        while (!is_space(s[i]) && s[i])
        {
            write(1, &s[i], 1);
            i ++;
        }
        if (is_space(s[i]) && i <= end)
        {
            write(1, " ", 1);
            i ++;
        }
        while (is_space(s[i]) && s[i] && i <= end)
            i ++;
    }
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        ft_print(argv[1]);
    }
    write(1, "\n", 1);
    return (0);
}