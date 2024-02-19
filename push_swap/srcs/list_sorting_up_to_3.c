/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sorting_up_to_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:48:30 by leanor            #+#    #+#             */
/*   Updated: 2024/02/19 15:52:56 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sort_2(t_dlist **stack)
{
	if (sort_check(*stack))
		return ;
	ft_sa(stack);
}

void	sort_3(t_dlist **stack)
{
	int	x;
	int	y;
	int	z;

	if (sort_check(*stack))
		return ;
	x = (*stack)->n_cont;
	y = (*stack)->next->n_cont;
	z = (*stack)->next->next->n_cont;
	if ((x < y && x < z) && y > z)
	{
		ft_sa(stack);
		ft_ra(stack);
	}
	else if (x < y && x > z)
		ft_rra(stack);
	else if (x < z && x > y)
		ft_sa(stack);
	else if (x > y && x > z)
	{
		ft_ra(stack);
		if (y > z)
			ft_sa(stack);
	}
}
