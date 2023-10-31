/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:55:02 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/05 12:08:43 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (nmemb > 2147483647 / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	total_size = nmemb * size;
	ft_bzero(ptr, total_size);
	return (ptr);
}

/* #include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	size_t nmemb = 2;
	size_t size = 0;

	int *arr = (int *)ft_calloc(nmemb, size);

	if (arr != NULL)
	{
		printf("My calloc Memory allocation successful.\n");

		// Print the allocated array to verify zero initialization
		printf("Allocated array: ");
		for (size_t i = 0; i < nmemb; i++)
		{
			printf("%d ", arr[i]);
		}
		printf("\n");

		free(arr); // Don't forget to free the allocated memory
	}
	else
	{
		printf("My calloc Memory allocation failed.\n");
	}
	int *arr2 = (int *)calloc(nmemb, size);

	if (arr2 != NULL)
	{
		printf("Original calloc Memory allocation successful.\n");

		// Print the allocated array to verify zero initialization
		printf("Allocated array: ");
		for (size_t i = 0; i < nmemb; i++)
		{
			printf("%d ", arr2[i]);
		}
		printf("\n");

		free(arr2); // Don't forget to free the allocated memory
	}
	else
	{
		printf("Original calloc Memory allocation failed.\n");
	}

	return 0;
} */