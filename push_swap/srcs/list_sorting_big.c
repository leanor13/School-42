/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sorting_big.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:59:33 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/19 15:45:04 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	move_node(t_dlist **stack_a, t_dlist **stack_b)
{
	t_dlist	*candidate;

	set_target(*stack_a, *stack_b);
	calc_prices(*stack_a, *stack_b);
	candidate = find_candidate(*stack_b);
	if (candidate->direct_rotate && candidate->target->direct_rotate)
		while (*stack_b != candidate && *stack_a != candidate->target)
			ft_rr(stack_a, stack_b);
	else if (!candidate->direct_rotate && !candidate->target->direct_rotate)
		while (*stack_b != candidate && *stack_a != candidate->target)
			ft_rrr(stack_a, stack_b);
	finish_rotating(stack_a, stack_b, candidate);
	ft_pa(stack_a, stack_b);
}

void	set_rotation_dir(t_dlist *stack)
{
	int	i;
	int	mid;

	mid = ft_dlstlen(stack) / 2;
	if (!stack)
		return ;
	i = 0;
	while (stack)
	{
		stack->curr_pos = i;
		if (i <= mid)
			stack->direct_rotate = true;
		else
			stack->direct_rotate = false;
		stack = stack->next;
		i++;
	}
}

void	big_sort(t_dlist **stack_a, t_dlist **stack_b)
{
	t_dlist	*first_elem;
	int		len_a;

	len_a = ft_dlstlen(*stack_a);
	while (len_a > 3)
	{
		ft_pb(stack_a, stack_b);
		len_a--;
	}
	sort_3(stack_a);
	while (*stack_b)
		move_node(stack_a, stack_b);
	set_rotation_dir(*stack_a);
	first_elem = ft_dlst_find_min(*stack_a);
	if (first_elem->direct_rotate)
		while ((*stack_a)->content != first_elem->content)
			ft_ra(stack_a);
	else
		while ((*stack_a)->content != first_elem->content)
			ft_rra(stack_a);
}
