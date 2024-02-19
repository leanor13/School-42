/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_operations_ab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:42:38 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/19 16:48:30 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_ss(t_dlist **stack_a, t_dlist **stack_b, bool silent)
{
	ft_swap(stack_a);
	ft_swap(stack_b);
	if (!silent)
		ft_putstr_fd("ss\n", 1);
}

void	ft_rr_both(t_dlist **stack_a, t_dlist **stack_b, bool silent)
{
	ft_rotate(stack_a);
	ft_rotate(stack_b);
	if (!silent)
		ft_putstr_fd("rr\n", 1);
}

void	ft_rrr(t_dlist **stack_a, t_dlist **stack_b, bool silent)
{
	ft_reverse_rotate(stack_a);
	ft_reverse_rotate(stack_b);
	if (!silent)
		ft_putstr_fd("rrr\n", 1);
}
