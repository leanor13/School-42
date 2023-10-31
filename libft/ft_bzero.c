/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:42:17 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/10 11:58:25 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		*ptr = '\0';
		ptr ++;
		i ++;
	}
}

/* #include <stdio.h>
#include <string.h>

int main()
{
    // Test 1: Zeroing out a single byte
    unsigned char data1[1] = {0x55};
    ft_bzero(data1, 1);

    printf("Test 1: Zeroing out a single byte\n");
    printf("Expected result: 0x00\n");
    printf("Actual result:   0x%02X\n", data1[0]);
    printf("\n");

    // Test 2: Zeroing out multiple bytes
    unsigned char data2[5] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
    ft_bzero(data2, 5);

    printf("Test 2: Zeroing out multiple bytes\n");
    printf("Expected result: 0x00 0x00 0x00 0x00 0x00\n");
    printf("Actual result:   ");
    for (int i = 0; i < 5; i++)
    {
        printf("0x%02X ", data2[i]);
    }
    printf("\n");
    printf("\n");

    // Test 3: Zeroing out a portion of an array
    unsigned char data3[8] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
    ft_bzero(data3 + 2, 4);

    printf("Test 3: Zeroing out a portion of an array\n");
    printf("Expected result: 0x00 0x11 0x00 0x00 0x00 0x00 0x66 0x77\n");
    printf("Actual result:   ");
    for (int i = 0; i < 8; i++)
    {
        printf("0x%02X ", data3[i]);
    }
    printf("\n");
    printf("\n");

    return 0;
} */