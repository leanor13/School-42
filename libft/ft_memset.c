/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:05:21 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/10 11:55:08 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*byte_ptr;
	unsigned char	byte_value;
	size_t			i;

	byte_ptr = ptr;
	byte_value = (unsigned char) value;
	i = 0;
	while (i < num)
	{
		byte_ptr[i] = byte_value;
		i ++;
	}
	return (ptr);
}

/* #include <stdio.h>
#include <string.h>

int main()
{
    // Test 1: Setting a single byte
    unsigned char data1[1];
    ft_memset(data1, 0x55, 1);

    printf("Test 1: Setting a single byte\n");
    printf("Expected result: 0x55\n");
    printf("Actual result:   0x%02X\n", data1[0]);
    printf("\n");

    // Test 2: Setting multiple bytes
    unsigned char data2[5];
    ft_memset(data2, 0xAA, 5);

    printf("Test 2: Setting multiple bytes\n");
    printf("Expected result: 0xAA 0xAA 0xAA 0xAA 0xAA\n");
    printf("Actual result:   ");
    for (int i = 0; i < 5; i++)
    {
        printf("0x%02X ", data2[i]);
    }
    printf("\n");
    printf("\n");

    // Test 3: Setting a portion of an array
    unsigned char data3[8] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
    ft_memset(data3 + 2, 0xBB, 4);

    printf("Test 3: Setting a portion of an array\n");
    printf("Expected result: 0x00 0x11 0xBB 0xBB 0xBB 0xBB 0x66 0x77\n");
    printf("Actual result:   ");
    for (int i = 0; i < 8; i++)
    {
        printf("0x%02X ", data3[i]);
    }
    printf("\n");
    printf("\n");

    return 0;
} */