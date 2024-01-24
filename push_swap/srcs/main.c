/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:18:35 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/24 14:58:09 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_isnum(char *s)
{
	if (*s == '-')
		s ++;
	if (!s || !*s)
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

t_dlist	**read_input(int ac, char **av)
{
	t_dlist	**stack;
	int		num;
	int		i;

	stack = ft_calloc(ac, sizeof(t_dlist *));
	if (!stack)
		return (NULL);
	i = 1;
	while (i < ac)
	{
		num = ft_atoi(av[i]);
		ft_dlstadd_back(stack, ft_dlstnew(num));
		i ++;
	}
	return (stack);
}

int	main(int ac, char **av)
{
	t_dlist	**stack_a;

	if (ac < 2)
	{
		ft_printf("Needed at least one integer");
		return (0);
	}
	if (validate_input(av, ac))
		stack_a = read_input(ac, av);
	ft_dlst_free(stack_a);
	return (0);
}
