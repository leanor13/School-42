/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:36:49 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/10 12:01:57 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	len;
	unsigned int	i;

	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		f(i, s);
		s ++;
		i ++;
	}
}

/* #include <stdio.h>
#include <string.h>

void print_index_and_char(unsigned int index, char *c)
{
    printf("Index: %u, Character: %c\n", index, *c);
}

int main()
{
    char str[] = "Hello, world!";

    printf("Original String: %s\n", str);

    printf("Testing ft_striteri:\n");
    ft_striteri(str, print_index_and_char);

    return 0;
} */