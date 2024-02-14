
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
		count ++;
		stack = stack->next;
	}
	return (1);
}

void	sort_2(t_dlist **stack, int order)
{
	if (sort_check(*stack, order, 2))
		return ;
	ft_sa(stack);
}
void	sort_3(t_dlist **stack, int order)
{
	int	x;
	int	y;
	int	z;

	if (sort_check(*stack, order, 3))
		return ;
	x = (*stack)->index;
	y = (*stack)->next->index;
	z = (*stack)->next->next->index;
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

void	quick_sort_a(t_dlist **stack_a, t_dlist **stack_b, int len)
{
	int		med;
	int		i;

	i = 0;
	med = ft_med_count(*stack_a, len);
	while (i < len)
	{
		if ((*stack_a)->index < med)
			ft_pb(stack_a, stack_b);
		else
			ft_ra(stack_a);
		i ++;
	}
	//quick_sort_a(stack_a, stack_b, len/2);
	//quick_sort_b(stack_a, stack_b, len/2);
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
			ft_rb(stack_b);
		i ++;
	}
	//quick_sort_a(stack_a, stack_b, len/2);
	//quick_sort_b(stack_a, stack_b, len/2);
}

void	sort_stack(t_dlist **stack_a, t_dlist **stack_b)
{
	int	size;

	(void)stack_b;
	size = ft_dlstlen(*stack_a);
	if (size == 2)
		sort_2(stack_a, ASC);
	else if (size == 3)
		sort_3(stack_a, ASC);
	//else if (size == 5)
		//quick_sort_a(stack_a, stack_b, ft_dlstlen(stack_a));
	else
		ft_printf("Not supported length");
}
