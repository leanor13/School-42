
#include "../includes/push_swap.h"

void	sort_2_a(t_dlist **stack_a, t_dlist **stack_b)
{
	if ((*stack_a)->index > (*stack_a)->next->index)
		ft_sa(stack_a, stack_b);
}
void	sort_2_b(t_dlist **stack_a, t_dlist **stack_b)
{
	if ((*stack_b)->index > (*stack_b)->next->index)
		ft_sb(stack_a, stack_b);
}
void	sort_3_a(t_dlist **stack_a, t_dlist **stack_b)
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
void	sort_3_b(t_dlist **stack_a, t_dlist **stack_b)
{
	int	x;
	int	y;
	int	z;

	x = (*stack_b)->index;
	y = (*stack_b)->next->index;
	z = (*stack_b)->next->next->index;
	if ((x < y && x < z) && y > z)
	{
		ft_sb(stack_a, stack_b);
		ft_rb(stack_a, stack_b);
	}
	else if (x < y && x > z)
			ft_rrb(stack_a, stack_b);
	else if (x < z && x > y)
			ft_sb(stack_a, stack_b);
	else if (x > y && x > z)
	{
		ft_rb(stack_a, stack_b);
		if (y > z)
			ft_sb(stack_a, stack_b);
	}
}

void	quick_sort_a(t_dlist **stack_a, t_dlist **stack_b, int len)
{
	int		med;
	int		i;

	i = 0;
	med = ft_med_count(stack_a, len);
	while (i < len)
	{
		if ((*stack_a)->index < med)
			ft_pb(stack_a, stack_b);
		else
			ft_ra(stack_a, stack_b);
		i ++;
	}
	quick_sort_a(stack_a, stack_b, len/2);
	quick_sort_b(stack_a, stack_b, len/2);
}
void	quick_sort_b(t_dlist **stack_a, t_dlist **stack_b, int len)
{
	int		med;
	int		i;

	i = 0;
	med = len/2;
	while (i < len)
	{
		if ((*stack_b)->index > med)
			ft_pa(stack_a, stack_b);
		else
			ft_rb(stack_a, stack_b);
		i ++;
	}
	quick_sort_a(stack_a, stack_b, len/2);
	quick_sort_b(stack_a, stack_b, len/2);
}

void	sort_stack(t_dlist **stack_a, t_dlist **stack_b)
{
	int	size;

	size = ft_dlstlen(*stack_a);
	if (size == 2)
		sort_2(stack_a, stack_b);
	else if (size == 3)
		sort_3(stack_a, stack_b);
	else if (size == 5)
		quick_sort_a(stack_a, stack_b, ft_dlstlen(stack_a));
	else
		ft_printf("Not supported length");
}
