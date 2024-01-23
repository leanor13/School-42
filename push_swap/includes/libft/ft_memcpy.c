/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:51:33 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/10 11:30:30 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*p_dest;
	unsigned char	*p_src;
	size_t			i;

	p_dest = (unsigned char *) dest;
	p_src = (unsigned char *) src;
	if (p_dest == NULL && p_src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		p_dest[i] = p_src[i];
		i ++;
	}
	return (dest);
}

/* #include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char src[] = "Hello, world!";
    char dest[50];

    // Using ft_memcpy
    ft_memcpy(dest, src, strlen(src) + 1);
    printf("ft_memcpy result: %s\n", dest);

    // Using standard memcpy for comparison
    char dest_std[50];
    memcpy(dest_std, src, strlen(src) + 1);
    printf("memcpy result: %s\n", dest_std);

    // Compare the results
    if (strcmp(dest, dest_std) == 0)
        printf("Both functions produced the same result.\n");
    else
        printf("Results differ between ft_memcpy and memcpy.\n");

    return 0;
} */