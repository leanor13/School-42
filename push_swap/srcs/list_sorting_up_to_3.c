/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sorting_up_to_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:48:30 by leanor            #+#    #+#             */
/*   Updated: 2024/02/19 17:22:32 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sort_2(t_dlist **stack)
{
	if (sort_check(*stack))
		return ;
	ft_s(stack, A, PRINT);
}

void	sort_3(t_dlist **stack)
{
	int	x;
	int	y;
	int	z;

	if (sort_check(*stack))
		return ;
	x = (*stack)->content;
	y = (*stack)->next->content;
	z = (*stack)->next->next->content;
	if ((x < y && x < z) && y > z)
	{
		ft_s(stack, A, PRINT);
		ft_r(stack, A, PRINT);
	}
	else if (x < y && x > z)
		ft_rr(stack, A, PRINT);
	else if (x < z && x > y)
		ft_s(stack, A, PRINT);
	else if (x > y && x > z)
	{
		ft_r(stack, A, PRINT);
		if (y > z)
			ft_s(stack, A, PRINT);
	}
}
