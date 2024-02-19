/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_operations_a.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:40:06 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/19 15:55:41 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sa(t_dlist **stack_a)
{
	ft_putstr_fd("sa\n", 1);
	ft_swap(stack_a);
}

void	ft_pa(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_putstr_fd("pa\n", 1);
	ft_push(stack_b, stack_a);
}

void	ft_ra(t_dlist **stack_a)
{
	ft_putstr_fd("ra\n", 1);
	ft_rotate(stack_a);
}

void	ft_rra(t_dlist **stack_a)
{
	ft_putstr_fd("rra\n", 1);
	ft_reverse_rotate(stack_a);
}
