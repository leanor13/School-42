/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:18:35 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/26 12:27:03 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_dlist	**read_input(int ac, char **av)
{
	t_dlist	**stack;
	t_dlist	*new_node;
	int		num;
	int		i;

	stack = ft_calloc(ac, sizeof(t_dlist *));
	if (!stack)
		return (ft_printf(ERROR_MALLOC), NULL);
	i = 1;
	while (i < ac)
	{
		num = ft_atoi(av[i]);
		new_node = ft_dlstnew(num);
		if (!new_node)
		{
			ft_dlst_free(stack);
			return (ft_printf(ERROR_MALLOC), NULL);
		}
		ft_dlstadd_back(stack, new_node);
		i ++;
	}
	if (has_duplicate(stack))
		ft_dlst_free(stack);
	return (stack);
}

void	print_stack(t_dlist **stack)
{
	t_dlist	*tmp;

	tmp = *stack;
	while (tmp)
	{
		ft_printf("%d\n", tmp->content);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av)
{
	t_dlist	**stack_a;
	t_dlist	**stack_b;

	stack_a = NULL;
	if (ac < 2)
	{
		ft_printf(ERROR_EMPTY_INPUT);
		return (0);
	}
	if (validate_input(av, ac))
	{
		stack_a = read_input(ac, av);
		if (!stack_a)
			return (0);
		stack_b = ft_calloc(ac, sizeof(t_dlist *));
		if (!stack_b)
			return (ft_printf(ERROR_MALLOC), 0);
		print_stack(stack_a);
		ft_dlst_free(stack_a);
		ft_dlst_free(stack_b);
	}
	return (0);
}
