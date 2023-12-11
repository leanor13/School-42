
#include <stdlib.h>

int     is_space(char c)
{
    return ((c > 8 && c < 15) || c == 32);
}

char    *save_word(char *str, size_t len)
{
    char    *word;
    size_t  i = 0;

    word = malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    word[len] = '\0';
    while (i < len)
    {
        word[i] = str[i];
        i ++;
    }
    return (word);
}

size_t  count_words(char *str)
{
    size_t counter = 0;

    while (is_space(*str))
        str ++;
    while (*str)
    {
        counter ++;
        while (!is_space(*str) && *str)
            str ++;
        while (is_space(*str))
            str ++;
    }
    return (counter);
}

char    **ft_split(char *str)
{
    char    **res;
    char    *begin;
    size_t  len = 0;
    size_t  i = 0;
    size_t  j = 0;
    size_t  words;

    words = count_words(str);
    res = malloc(sizeof(char *) * (words + 1));
    if (!res)
        return (NULL);
    while (i < words)
    {
        while (is_space(*str))
            str ++;
        len = 0;
        begin = str;
        while (!is_space(*str) && *str)
        {   
            str ++;
            len ++;
        }
        res[i] = save_word(begin, len);
        if (res[i] == NULL)
        {
            while (j < i)
            {
                free(res[j]);
                j ++;
            }
            free(res);
            return (NULL);
        }
        i ++;
    }
    res[i] = NULL;
    return (res);
}

/* #include <stdio.h>

int     main(int ac, char **av)
{    
    char **res;
    int     i = 0;

    if (ac == 2)
    {
        res = ft_split(av[1]);
        while (res[i] != NULL)
        {
            printf("%s\n", res[i]);
            i ++;
        }
        //free(res);
    }
    
    return (0);
} */