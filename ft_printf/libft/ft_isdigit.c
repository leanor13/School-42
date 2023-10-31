/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:25:55 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/05 12:12:19 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (ft_isascii(c))
		return (c >= '0' && c <= '9');
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
				if (!!ft_isdigit(i) != !!isdigit(i))
					printf("%d\n", i);
				i++;
			}
	return (0);
}*/