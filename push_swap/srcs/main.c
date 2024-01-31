/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:18:35 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/31 15:36:23 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	print_stack(t_dlist *stack)
{
	t_dlist	*tmp;
	int		content;
	int		index;

	tmp = stack;
	while (tmp)
	{
		content = tmp->content;
        index = tmp->index;
		//ft_printf("content: %d, index: %d\n", content, index);
        ft_printf("content: %d", content);
        ft_printf(" index: %d\n", index);
		tmp = tmp->next;
	}
}

t_dlist	*construct_input(int ac, char **av)
{
	t_dlist	*stack;

	stack = NULL;
	if (ac < 2 || !all_is_num(av, ac))
		return (NULL);
	stack = read_input(ac, av);
	if (!stack)
		return (NULL);
	calculate_indexes(&stack);
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
		return (ft_printf(ERROR), 0);
	}
	print_stack(stack_a);
	ft_dlst_free(&stack_a);
	ft_dlst_free(&stack_b);

	return (0);
}
