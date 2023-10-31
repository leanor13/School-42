/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:31:06 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/04 13:32:37 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	int	i = 0;

	while (i < 530)
			{
				if (ft_tolower(i) != tolower(i))
					printf("%d\n", i);
				i++;
			}
	return (0);
}*/