
#include "../includes/push_swap.h"

void	sort_2(t_dlist **stack_a, t_dlist **stack_b)
{
	if ((*stack_a)->index > (*stack_a)->next->index)
		ft_sa(stack_a, stack_b);
}

void	sort_3(t_dlist **stack_a, t_dlist **stack_b)
{
	if ((*stack_a)->index == 0 && (*stack_a)->next->index == 2)
	{
		ft_sa(stack_a, stack_b);
		ft_ra(stack_a, stack_b);
	}
	else if ((*stack_a)->index == 1)
	{
		if ((*stack_a)->next->index == 2)
			ft_rra(stack_a, stack_b);
		else
			ft_sa(stack_a, stack_b);
	}
	else if ((*stack_a)->index == 2)
	{
		ft_ra(stack_a, stack_b);
		if ((*stack_a)->index == 1)
			ft_sa(stack_a, stack_b);
	}
}
void	sort_stack(t_dlist **stack_a, t_dlist **stack_b)
{
	int	size;

	size = ft_dlstlen(*stack_a);
	if (size == 2)
		sort_2(stack_a, stack_b);
	else if (size == 3)
		sort_3(stack_a, stack_b);
	else
		ft_printf("Too long to sort yet\n");
}
