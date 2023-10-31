/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:04:57 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/10 11:53:06 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*p_dest;
	unsigned char	*p_src;

	p_dest = (unsigned char *) dest;
	p_src = (unsigned char *) src;
	if (p_dest > p_src && p_dest < p_src + n)
	{
		p_dest += n - 1;
		p_src += n - 1;
		while (n > 0)
		{
			*p_dest-- = *p_src--;
			n--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

/* #include <string.h>
#include <stdio.h>

int main()
{
	char src[] = "Hello, world!";
	char dest[50];
	char original[50];

	// Copy the source to the original
	strcpy(original, src);

	// Intentionally create an overlap situation
	char *src_overlap = src; // "world!" starts at index 6
	char *dest_overlap = dest + 6; // Overlap with src

	// After using ft_memmove with an overlap
	ft_memmove(dest_overlap, src_overlap, strlen(src_overlap) + 1);

	// Print the contents of the dest array
	printf("Contents of dest after ft_memmove with overlap: ");
	for (size_t i = 0; i < sizeof(dest); i++) {
		printf("%c", dest[i]);
	}
	printf("\n");

	// Reset the destination and perform a non-overlapping copy
	memset(dest, 0, sizeof(dest));
	ft_memmove(dest, src, strlen(src) + 1);

	// Check if the non-overlapping move was correct
	if (strcmp(dest, src) == 0)
		printf("ft_memmove result without overlap is correct: %s\n", dest);
	else
		printf("ft_memmove result without overlap is incorrect: %s\n", dest);

	return 0;
} */