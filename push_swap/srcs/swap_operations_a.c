/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_operations_a.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:40:06 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/19 13:45:21 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sa(t_dlist **stack_a)
{
	ft_printf("sa\n");
	ft_swap(stack_a);
}

void	ft_pa(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_printf("pa\n");
	ft_push(stack_b, stack_a);
}

void	ft_ra(t_dlist **stack_a)
{
	ft_printf("ra\n");
	ft_rotate(stack_a);
}

void	ft_rra(t_dlist **stack_a)
{
	ft_printf("rra\n");
	ft_reverse_rotate(stack_a);
}
