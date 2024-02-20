/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:52:41 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/20 13:42:10 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	main(int ac, char **av)
{
	t_dlist	*stack_a;
	t_dlist	*stack_b;

	if (ac >= 2 || (ac != 2 || *av[1] != '\0'))
	{
		stack_a = construct_input(ac - 1, av + 1);
		stack_b = NULL;
	}
	else
	{
		check_sorted_stack();
		return (0);
	}
	if (!stack_a)
	{
		ft_dlst_free(&stack_a);
		ft_dlst_free(&stack_b);
		return (ft_putstr_fd(ERROR, 2), 0);
	}
	
	ft_dlst_free(&stack_a);
	ft_dlst_free(&stack_b);
	return (0);
}
