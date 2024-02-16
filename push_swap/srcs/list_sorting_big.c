
#include "../includes/push_swap.h"

void	big_sort(t_dlist **stack_a, t_dlist **stack_b)
{
	t_dlist	*first_elem;
	int		len_a;

	len_a = ft_dlstlen(*stack_a);
	while (len_a > 3)
	{
		pb(stack_a, stack_b);
	}
	sort_3(stack_a, ASC);
	while (*stack_b)
	{
		calc_prices(*stack_a, *stack_b);
		move_cand(stack_a, stack_b);
	}
	set_med(stack_a);
	first_elem = find_first(*stack_a);
	if (first_elem->above_med)
		while (*stack_a != first_elem)
			ra(stack_a);
	else
		while (*stack_a != first_elem)
			rra(stack_a);
}
