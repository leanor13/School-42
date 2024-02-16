/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:18:35 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/16 11:15:00 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdio.h>

void	print_stack(t_dlist *stack)
{
	t_dlist	*tmp;
	int		content;
	int		index;

	tmp = stack;
	while (tmp)
	{
		content = tmp->content;
        index = tmp->n_cont;
		printf("content: %d, index: %d\n", content, index);
		tmp = tmp->next;
	}
}

t_dlist	*construct_input(int ac, char **av)
{
	t_dlist	*stack;

	stack = NULL;
	if (ac == 2)
	{
		av = ft_split(ft_strjoin("a ", av[1]), ' ');
		ac = 0;
		while (av[ac])
			ac ++;
	}
	if (ac < 2 || !all_is_num(av, ac))
		return (NULL);
	stack = read_input(ac, av);
	if (!stack)
		return (NULL);
	calculate_indexes(&stack, ft_dlstlen(stack));
	return (stack);
}

int	main(int ac, char **av)
{
	t_dlist	*stack_a;
	t_dlist	*stack_b;

	stack_a = construct_input(ac, av);
	stack_b = NULL;
	if (!stack_a)
	{
		ft_dlst_free(&stack_a);
		ft_dlst_free(&stack_b);
		return (ft_putstr_fd(ERROR, 2), 0);
	}
	//ft_printf("Original stack:\n");
	//print_stack(stack_a);
	sort_stack(&stack_a, &stack_b);
	//printf("Stack b size: %d, Sorted stack a (expected 1):%d\n", 
	//			ft_dlstlen(stack_b),
	//			sort_check(stack_a, ASC, ft_dlstlen(stack_a)));
	//print_stack(stack_a);
	//ft_printf("Sorted stack b:\n", ft_dlstlen(stack_b));
	//print_stack(stack_b);
	ft_dlst_free(&stack_a);
	ft_dlst_free(&stack_b);
	return (0);
}
