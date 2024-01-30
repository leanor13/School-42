/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:18:35 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/30 16:30:53 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	print_stack(t_dlist *stack)
{
	t_dlist	*tmp;

	tmp = stack;
	while (tmp)
	{
		ft_printf("%d\n", tmp->content);
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
	//free(stack_a);
	//free(stack_b);

	return (0);
}
