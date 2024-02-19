/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_operations_b.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:49:42 by leanor            #+#    #+#             */
/*   Updated: 2024/02/19 15:56:22 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sb(t_dlist **stack_b)
{
	ft_putstr_fd("sb\n", 1);
	ft_swap(stack_b);
}

void	ft_pb(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_putstr_fd("pb\n", 1);
	ft_push(stack_a, stack_b);
}

void	ft_rb(t_dlist **stack_b)
{
	ft_putstr_fd("rb\n", 1);
	ft_rotate(stack_b);
}

void	ft_rrb(t_dlist **stack_b)
{
	ft_putstr_fd("rrb\n", 1);
	ft_reverse_rotate(stack_b);
}
