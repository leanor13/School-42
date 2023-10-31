/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:20:41 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/05 12:10:39 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (ft_isascii(c))
		return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
	else
		return (0);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	int	i = 0;

	while (i < 530)
			{
				if (!!ft_isalpha(i) != !!isalpha(i))
					printf("Wrong for i: %d value: %c, isalpha:%d \n", i, i, isalpha(i));
				i++;
			}
	return (0);
}*/