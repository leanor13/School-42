
#include "../includes/push_swap.h"

void	set_mid(t_dlist *stack)
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
			stack->first_half = false;
		else
			stack->first_half = true;
		stack = stack->next;
		i++;
	}
}
void	set_target(t_dlist *stack_a, t_dlist *stack_b)
{
	t_dlist	*curr_a;
	t_dlist	*target;
	long	match_ind;

	while(stack_b)
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

/*
TODO: maybe calc prices for both stacks. 
Then have a function to calc move price for b.
*/
void	calc_prices(t_dlist *stack_a, t_dlist *stack_b)
{
	int	len_a;
	int	len_b;

	len_a = ft_dlstlen(stack_a);
	len_b = ft_dlstlen(stack_b);
	while (stack_b)
	{
		if (stack_b->first_half)
			stack_b->move_price = stack_b->curr_pos;
		else
			stack_b->move_price = len_b - stack_b->curr_pos;
		if (stack_b->target->first_half)
			stack_b->move_price += stack_b->target->curr_pos;
		else
			stack_b->move_price += len_a - stack_b->target->curr_pos;
		stack_b = stack_b->next;
	}
}
t_dlist	*find_candidate(t_dlist *stack_b)
{
	int	min_price;
	t_dlist *curr_candidate;

	if (!stack_b)
		return (NULL);
	min_price = stack_b->move_price;
	while (stack_b)
	{
		if (stack_b->move_price < min_price)
		{
			min_price = stack_b->move_price;
			curr_candidate = stack_b;
		}
		stack_b = stack_b->next;
	}
	return (curr_candidate);
}
/*
TODO: improve: rotate both or rr both
*/
void	move_candidate(t_dlist **stack_a, t_dlist **stack_b)
{
	t_dlist *candidate;

	candidate = find_candidate(*stack_b);
	if (candidate->first_half)
	{
		while (*stack_b != candidate)
			ft_rb(stack_b);
	}
	else
	{
		while (*stack_b != candidate)
			ft_rrb(stack_b);
	}
	if (candidate->target->first_half)
	{
		while (*stack_a != candidate->target)
			ft_ra(stack_a);
	}
	else
	{
		while (*stack_a != candidate->target)
			ft_rra(stack_a);
	}
	ft_pa(stack_a, stack_b);
}

t_dlist	*find_first(t_dlist *stack)
{
	if (!stack)
		return (NULL);
	while (stack)
	{
		if(stack->n_cont == 0)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
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
	sort_3(stack_a, ASC);
	while (*stack_b)
	{
		set_mid(*stack_b);
		set_mid(*stack_a);
		set_target(*stack_a, *stack_b);
		ft_putstr_fd("calc prices\n", 2);
		calc_prices(*stack_a, *stack_b);
		ft_putstr_fd("move cand\n", 2);
		move_candidate(stack_a, stack_b);
	}
	ft_putstr_fd("set mid\n", 2);
	set_mid(*stack_a);
	first_elem = find_first(*stack_a);
	if (!first_elem)
	{
		ft_putstr_fd("No first elem\n", 2);
		return ;
	}
	if (first_elem->first_half)
		while (*stack_a != first_elem)
			ft_ra(stack_a);
	else
		while (*stack_a != first_elem)
			ft_rra(stack_a);
}
