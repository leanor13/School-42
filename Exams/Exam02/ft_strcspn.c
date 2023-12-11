#include <unistd.h>

int ft_char_in_str(char c, char *str)
{
    while (*str)
    {
        if (c == *str)
            return (1);
        str ++;
    }
    return (0);
}

size_t	ft_strcspn(const char *s, const char *rej)
{
    size_t  i;
    char    *reject;
    
    reject = (char *)rej;
    i = 0;
    while (s[i] && !ft_char_in_str(s[i], reject))
        i ++;
    return (i);
}

/* #include <string.h>
#include <stdio.h>

int main(void)
{
    printf("my fun: %zu\n", ft_strcspn("Hello", "edfH"));
    printf("orig fun: %zu\n", strcspn("Hello", "edfH"));

    return (0);
} */