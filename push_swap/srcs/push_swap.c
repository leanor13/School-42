
#include "../includes/push_swap.h"

void	sort_2(t_dlist **stack_a, t_dlist **stack_b)
{
	if ((*stack_a)->index > (*stack_a)->next->index)
		ft_sa(stack_a, stack_b);
}

void	sort_3(t_dlist **stack_a, t_dlist **stack_b)
{
	int	x;
	int	y;
	int	z;

	x = (*stack_a)->index;
	y = (*stack_a)->next->index;
	z = (*stack_a)->next->next->index;
	if ((x < y && x < z) && y > z)
	{
		ft_sa(stack_a, stack_b);
		ft_ra(stack_a, stack_b);
	}
	else if (x < y && x > z)
			ft_rra(stack_a, stack_b);
	else if (x < z && x > y)
			ft_sa(stack_a, stack_b);
	else if (x > y && x > z)
	{
		ft_ra(stack_a, stack_b);
		if (y > z)
			ft_sa(stack_a, stack_b);
	}
}
void	sort_5(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_sa(stack_a, stack_b);
	return ;
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
