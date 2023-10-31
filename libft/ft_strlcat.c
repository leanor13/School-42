/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:21:06 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/05 18:37:24 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_l;
	size_t	src_l;

	i = 0;
	dest_l = ft_strlen(dest);
	j = dest_l;
	src_l = ft_strlen(src);
	if (size == 0 || size <= dest_l)
		return (src_l + size);
	while (src[i] != '\0' && i < size - dest_l - 1)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest_l + src_l);
}
/*
int main(void)
{
    char dest[20]; // Destination buffer
    char ft_dest[20]; // Destination buffer for ft_strlcat
    char *src; // Source string
    unsigned int size; // Size of the destination buffer

    // Test cases

    // Test 1: Destination buffer is empty, should copy the entire source string
    src = "Hello";
    size = 10;
    ft_dest[0] = '\0'; // Initialize ft_dest as an empty string
    printf("Test 1:\n");
    printf("Custom ft_strlcat: %u\n", ft_strlcat(ft_dest, src, size));
    printf("Result: %s\n\n", ft_dest);

    // Test 2: Destination buffer is too small to fit the entire source string
    src = "World";
    size = 5;
    strcpy(dest, "Hello");
    strcpy(ft_dest, "Hello");
    printf("Test 2:\n");
    printf("Custom ft_strlcat: %u\n", ft_strlcat(ft_dest, src, size));
    printf("Result: %s\n\n", ft_dest);

    // Test 3: Destination buffer has exactly enough space to fit both strings
    src = "World";
    size = 11;
    strcpy(dest, "Hello");
    strcpy(ft_dest, "Hello");
    printf("Test 3:\n");
    printf("Custom ft_strlcat: %u\n", ft_strlcat(ft_dest, src, size));
    printf("Result: %s\n\n", ft_dest);

    return 0;
}*/
