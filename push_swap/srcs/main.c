/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:18:35 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/29 13:48:02 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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
		return (ft_printf(ERROR), 0);
	if (validate_input(av, ac))
	{
		stack_a = read_input(ac, av);
		if (!stack_a)
			return (ft_printf(ERROR), 0);
		stack_b = ft_calloc(ac, sizeof(t_dlist *));
		if (!stack_b)
		{
			ft_dlst_free(stack_a);
			return (ft_printf(ERROR), 0);
		}
		//print_stack(stack_a);
		ft_dlst_free(stack_b);
	}
	return (0);
}
