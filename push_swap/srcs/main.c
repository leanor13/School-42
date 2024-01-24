/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:18:35 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/24 14:31:36 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int ft_isnum(char *s)
{
	if (*s == '-')
		s ++;
	if (!s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		else
			s ++;
	}
	return (1);
}

int	validate_input(char **av, size_t ac)
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

t_dlist **read_input(size_t nmemb, char **av)
{
	t_dlist **stack_a;
	t_dlist	*next;
	t_dlist	*prev;
	int		num;
	int		i;

	stack_a = ft_calloc(nmemb, sizeof(t_dlist *));
	if (!stack_a)
		return (NULL);
	prev = NULL;
	i = 1;
	while (i < nmemb)
	{
		num = ft_atoi(av[i]);
		ft_dlstadd_back(stack_a, ft_dlstnew(num));
		i ++;
	}
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

