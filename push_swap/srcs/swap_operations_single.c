/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_operations_single.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:40:06 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/19 16:56:17 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_s(t_dlist **stack, int where, bool silent)
{
	if (!silent)
	{
		if (where == A)
			ft_putstr_fd("sa\n", 1);
		else if (where == B)
			ft_putstr_fd("sb\n", 1);
	}
	ft_swap(stack);
}

void	ft_p(t_dlist **stack_a, t_dlist **stack_b, int where, bool silent)
{
	if (where == A)
	{
		if (!silent)
			ft_putstr_fd("pa\n", 1);
		ft_push(stack_b, stack_a);
	}
	else if (where == B)
	{
		if (!silent)
			ft_putstr_fd("pb\n", 1);
		ft_push(stack_a, stack_b);
	}
}

void	ft_r(t_dlist **stack, int where, bool silent)
{
	if (!silent)
	{
		if (where == A)
			ft_putstr_fd("ra\n", 1);
		else if (where == B)
			ft_putstr_fd("rb\n", 1);
	}
	ft_rotate(stack);
}

void	ft_rr(t_dlist **stack, int where, bool silent)
{
	if (!silent)
	{
		if (where == A)
			ft_putstr_fd("rra\n", 1);
		else if (where == B)
			ft_putstr_fd("rrb\n", 1);
	}
	ft_reverse_rotate(stack);
}

