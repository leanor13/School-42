/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:18:35 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/23 17:11:22 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int ft_isnum(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		else
			s ++;
	}
	return (1);
}

int	validate_input(char **av, int ac)
{
	while (ac >= 2)
	{
		if (!ft_isnum(av[ac - 1]))
		{
			ft_printf("Invalid input, only digits are allowed");
			return (0);
		}
		ac --;
	}
	return (1);
}

int	main(int ac, char **av)
{
	if (ac == 1)
	{
		ft_printf("needed at least one integer");
		return (0);
	}
	if (validate_input(av, ac))
		ft_printf("input is valid");
	return (0);
}

