/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sorting_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:28:30 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/19 16:58:57 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	set_target(t_dlist *stack_a, t_dlist *stack_b)
{
	t_dlist	*curr_a;
	t_dlist	*target;
	long	match_ind;

	set_rotation_dir(stack_b);
	set_rotation_dir(stack_a);
	while (stack_b)
	{
		match_ind = LONG_MAX;
		curr_a = stack_a;
		while (curr_a)
		{
			if (curr_a->n_cont > stack_b->n_cont && curr_a->n_cont < match_ind)
			{
				match_ind = curr_a->n_cont;
				target = curr_a;
			}
			curr_a = curr_a->next;
		}
		if (match_ind == LONG_MAX)
			stack_b->target = ft_dlst_find_min(stack_a);
		else
			stack_b->target = target;
		stack_b = stack_b->next;
	}
}

static int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/*
TODO: maybe calc prices for both stacks.
Then have a function to calc move price for b.
*/
void	calc_prices(t_dlist *stack_a, t_dlist *stack_b)
{
	int	len_a;
	int	len_b;
	int	price_a;

	len_a = ft_dlstlen(stack_a);
	len_b = ft_dlstlen(stack_b);
	while (stack_b)
	{
		if (stack_b->direct_rotate)
			stack_b->move_price = stack_b->curr_pos;
		else
			stack_b->move_price = len_b - stack_b->curr_pos;
		if (stack_b->target->direct_rotate)
			price_a = stack_b->target->curr_pos;
		else
			price_a = len_a - stack_b->target->curr_pos;
		if (stack_b->direct_rotate != stack_b->target->direct_rotate)
			stack_b->move_price += price_a;
		else
			stack_b->move_price = max(stack_b->move_price, price_a);
		stack_b = stack_b->next;
	}
}

t_dlist	*find_candidate(t_dlist *stack_b)
{
	int		min_price;
	t_dlist	*curr_candidate;

	if (!stack_b)
		return (NULL);
	min_price = stack_b->move_price;
	curr_candidate = stack_b;
	while (stack_b)
	{
		if (stack_b->move_price < min_price || (stack_b->move_price <= min_price
				&& stack_b->direct_rotate == stack_b->target->direct_rotate))
		{
			min_price = stack_b->move_price;
			curr_candidate = stack_b;
		}
		stack_b = stack_b->next;
	}
	return (curr_candidate);
}

void	finish_rotating(t_dlist **stack_a, t_dlist **stack_b,
		t_dlist *candidate)
{
	if (candidate->direct_rotate)
		while (*stack_b != candidate)
			ft_r(stack_b, B, PRINT);
	else
		while ((*stack_b) != candidate)
			ft_rr(stack_b, B, PRINT);
	if (candidate->target->direct_rotate)
		while (*stack_a != candidate->target)
			ft_r(stack_a, A, PRINT);
	else
		while (*stack_a != candidate->target)
			ft_rr(stack_a, A, PRINT);
}
