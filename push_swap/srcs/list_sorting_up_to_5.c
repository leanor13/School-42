/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sorting_up_to_5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:48:30 by leanor            #+#    #+#             */
/*   Updated: 2024/02/19 11:59:41 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	sort_check(t_dlist *stack, int order, int len)
{
	int	count;

	count = 0;
	while (stack->next && count < len)
	{
		if (order == ASC && (stack->content > stack->next->content))
			return (0);
		if (order == DESC && (stack->content < stack->next->content))
			return (0);
		count++;
		stack = stack->next;
	}
	return (1);
}

void	sort_2(t_dlist **stack, int order)
{
	if (sort_check(*stack, order, 2))
		return ;
	if (order == ASC)
		ft_sa(stack);
	else
		ft_sb(stack);
}
void	sort_3(t_dlist **stack, int order)
{
	int	x;
	int	y;
	int	z;

	if (sort_check(*stack, order, 3))
		return ;
	x = (*stack)->n_cont;
	y = (*stack)->next->n_cont;
	z = (*stack)->next->next->n_cont;
	if (order == ASC)
	{
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
	else
	{
		if ((x > y && x > z) && y < z)
		{
			ft_sb(stack);
			ft_rb(stack);
		}
		else if (x > y && x < z)
			ft_rrb(stack);
		else if (x > z && x < y)
			ft_sb(stack);
		else if (x < y && x < z)
		{
			ft_rb(stack);
			if (y < z)
				ft_sb(stack);
		}
	}
}

int	quick_sort_a(t_dlist **stack_a, t_dlist **stack_b, int len)
{
	int	med;
	int	count;
	int	i;

	if (sort_check(*stack_a, ASC, len))
		return (1);
	if (len < 2)
		return (1);
	if (len == 2)
	{
		sort_2(stack_a, ASC);
		return (1);
	}
	if (len == 3)
	{
		sort_3(stack_a, ASC);
		return (1);
	}
	med = ft_med_count(*stack_a, len);
	count = 0;
	i = 0;
	while (count < len)
	{
		if ((*stack_a)->n_cont < med)
		{
			ft_pb(stack_a, stack_b);
			i++;
		}
		else
			ft_ra(stack_a);
		count++;
	}
	quick_sort_a(stack_a, stack_b, len - i);
	quick_sort_b(stack_a, stack_b, i);
	return (1);
}

int	quick_sort_b(t_dlist **stack_a, t_dlist **stack_b, int len)
{
	int	med;
	int	count;
	int	i;

	if (sort_check(*stack_b, DESC, len) || len < 2)
	{
		while (len > 0)
		{
			ft_pa(stack_a, stack_b);
			len--;
		}
		return (1);
	}
	med = ft_med_count(*stack_b, len);
	count = 0;
	i = 0;
	while (count < len)
	{
		if ((*stack_b)->n_cont >= med)
		{
			ft_pa(stack_a, stack_b);
			i++;
		}
		else
		{
			ft_rb(stack_b);
			count++;
		}
	}
	quick_sort_b(stack_a, stack_b, len - i);
	quick_sort_a(stack_a, stack_b, i);
	return (1);
}

void	sort_stack(t_dlist **stack_a, t_dlist **stack_b)
{
	int	size;

	size = ft_dlstlen(*stack_a);
	if (size == 2)
		sort_2(stack_a, ASC);
	else if (size == 3)
		sort_3(stack_a, ASC);
	else if (size <= 5)
		quick_sort_a(stack_a, stack_b, size);
	else if (size > 5)
		big_sort(stack_a, stack_b);
}
